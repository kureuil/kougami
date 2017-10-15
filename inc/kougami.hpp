#pragma once

#ifndef KOUGAMI_KOUGAMI_HPP
#define KOUGAMI_KOUGAMI_HPP 1

#include <functional>
#include <memory>
#include <ostream>
#include <unordered_map>
#include <vector>

#include "clang.hpp"

namespace kougami {
using clang::Cursor;
using clang::Result;

class Error {
  clang::SourceLocation _location;
  std::string _where;
  std::string _what;

 public:
  Error() = delete;
  Error(clang::SourceLocation const &location, std::string const &message);
  Error(Error const &error) = default;
  Error(Error &&error) = default;
  ~Error() = default;
  Error &operator=(Error const &error) = default;
  Error &operator=(Error &&error) = default;
  clang::SourceLocation const &location() const;
  std::string const &where() const;
  std::string const &what() const;
};

std::ostream &operator<<(std::ostream &stream, Error const &error);

class LinterVisitor : public clang::Visitor {
 protected:
  std::vector<Error> _errors = {};

  void check_cursor_is_in_header(Cursor const &cursor);

  void check_cursor_is_in_source(Cursor const &cursor);

 public:
  std::vector<Error> const &errors() const;

  Result visit_var_decl(Cursor const &, Cursor const &) override;

  Result visit_decl_stmt(Cursor const &, Cursor const &) override;

  Result visit_unknown(Cursor const &, Cursor const &) override;
};

enum class RuleKind {
  Warning,
  Error,
};

struct Rule {
  RuleKind kind;
  size_t id;
  std::function<std::unique_ptr<LinterVisitor>()> factory;
};

namespace linters {
class IdentifierCase : public LinterVisitor {
  void check_identifier_case(Cursor const &cursor);

 public:
  Result visit_function_decl(Cursor const &, Cursor const &) override;

  Result visit_var_decl(Cursor const &, Cursor const &) override;

  Result visit_parm_decl(Cursor const &, Cursor const &) override;

  Result visit_typedef_decl(Cursor const &, Cursor const &) override;
};

class MacroCase : public LinterVisitor {
 public:
  Result visit_macro_definition(Cursor const &, Cursor const &) override;
};

class MacroLocation : public LinterVisitor {
 public:
  Result visit_macro_definition(Cursor const &, Cursor const &) override;
};

class NoMultilineMacro : public LinterVisitor {
 public:
  Result visit_macro_definition(Cursor const &, Cursor const &) override;
};

class TypedefLocation : public LinterVisitor {
 public:
  Result visit_typedef_decl(Cursor const &, Cursor const &) override;
};

class TypedefName : public LinterVisitor {
  public:
    Result visit_typedef_decl(Cursor const &, Cursor const &) override;
};

class NoStructCopy : public LinterVisitor {
 public:
  Result visit_parm_decl(Cursor const &, Cursor const &) override;
};

class GlobalVarLocation : public LinterVisitor {
 public:
  Result visit_var_decl(Cursor const &, Cursor const &) override;
};

class ArgumentCount : public LinterVisitor {
 public:
  Result visit_function_decl(Cursor const &, Cursor const &) override;
};

class FunctionCount : public LinterVisitor {
  struct File {
    unsigned functions = 0;
  };

  std::unordered_map<std::string, File> _files = {};

 public:
  Result visit_function_decl(Cursor const &, Cursor const &) override;
};

class FunctionLength : public LinterVisitor {
 public:
  Result visit_compound_stmt(Cursor const &, Cursor const &) override;
};

class BreakAfterControl : public LinterVisitor {
 public:
  Result visit_compound_stmt(Cursor const &, Cursor const &) override;
};

class NoSpaceAfterUnary : public LinterVisitor {
 public:
  Result visit_unary_operator(Cursor const &, Cursor const &) override;
};

class SpaceAroundBinary : public LinterVisitor {
 public:
  Result visit_binary_operator(Cursor const &, Cursor const &) override;
};
}
}

#endif  // !KOUGAMI_KOUGAMI_HPP
