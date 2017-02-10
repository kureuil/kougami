#pragma once

#ifndef KOUGAMI_CLANG_HPP
#define KOUGAMI_CLANG_HPP 1

#include <clang-c/Index.h>
#include <ostream>
#include <string>

namespace clang {
/// A libclang index. Used to create translation units.
class Index {
  CXIndex _index;

 public:
  /// Create an index with the default flags.
  ///
  /// This means enabling PCH and disabling diagnostics.
  Index();
  Index(Index const &index) = delete;
  Index(Index &&index) = default;
  /// Destroy an index, and dispose of the underlying index.
  ///
  /// Calls clang_disposeIndex.
  ~Index();
  Index &operator=(Index const &index) = delete;
  Index &operator=(Index &&index) = default;
  /// Get the raw CXIndex.
  operator CXIndex() const;
};

/// A libclang CXString
class String {
  CXString _string;

 public:
  String() = delete;
  /// Create a String from a CXString.
  String(CXString string);
  String(String const &string) = delete;
  String(String &&string) = default;
  /// Destroy the string, disposing of the underlying CXString.
  ~String();
  String &operator=(String const &string) = delete;
  String &operator=(String &&string) = default;
  /// Get the raw string as a const char *.
  char const *c_str() const;
  /// Convert to a std::string
  operator std::string() const;
};

/// Print a String to a stream
std::ostream &operator<<(std::ostream &stream, String const &string);

/// A libclang file.
class File {
  CXFile _file;

 public:
  File() = delete;
  /// Create a fle from a CXFile
  File(CXFile file);
  File(File const &file) = default;
  File(File &&file) = default;
  ~File() = default;
  File &operator=(File const &file) = default;
  File &operator=(File &&file) = default;
  /// Get the raw CXFile.
  operator CXFile() const;
  /// Get the file name.
  String name() const;
  /// Compare two File for equality.
  bool operator==(File const &rhs) const;
  /// Compare two File for inequality.
  bool operator!=(File const &rhs) const;
  // /// Check is header guards are present
  // bool is_multiple_include_guarded() const;
};

/// A libclang source location.
class SourceLocation {
  CXSourceLocation _location;
  CXFile _file;
  unsigned _line;
  unsigned _column;
  unsigned _offset;

 public:
  /// Create a null SourceLocation
  SourceLocation();
  /// Create a SourceLocation from a CXSourceLocation
  SourceLocation(CXSourceLocation location);
  SourceLocation(SourceLocation const &location) = default;
  SourceLocation(SourceLocation &&location) = default;
  ~SourceLocation() = default;
  SourceLocation &operator=(SourceLocation const &location) = default;
  SourceLocation &operator=(SourceLocation &&location) = default;
  /// Get the raw CXSourceLocation.
  operator CXSourceLocation() const;
  /// Get the location's File
  File file() const;
  /// Get the location's line
  unsigned line() const;
  /// Get the location's column
  unsigned column() const;
  /// Is the location from main file?
  bool is_from_main_file() const;
  /// Is the locaton in a system header file?
  bool is_in_system_header() const;
};

/// Print a source location (file:column:line) to a stream
std::ostream &operator<<(std::ostream &stream, SourceLocation const &location);

/// A libclang CXCursorKind
class CursorKind {
  CXCursorKind _kind;

 public:
  CursorKind() = delete;
  /// Create a CursorKind from a CXCursorKind
  CursorKind(CXCursorKind kind);
  CursorKind(CursorKind const &kind) = default;
  CursorKind(CursorKind &&kind) = default;
  ~CursorKind() = default;
  CursorKind &operator=(CursorKind const &kind) = default;
  CursorKind &operator=(CursorKind &&kind) = default;
  /// Compare a CursorKind to a CXCursorKind
  bool operator==(CXCursorKind rhs) const;
  bool operator!=(CXCursorKind rhs) const;
  /// Get the raw CursorKind
  operator CXCursorKind() const;
  /// Get the cursor kind's name.
  String spelling() const;
  // Not sure if I should be creating a brand new String each time.
};

/// A libclang type.
class Type {
  CXType _type;

 public:
  Type() = delete;
  /// Create a Type from a CXType
  Type(CXType type);
  Type(Type const &type) = default;
  Type(Type &&type) = default;
  ~Type() = default;
  Type &operator=(Type const &type) = default;
  Type &operator=(Type &&type) = default;
  /// Get the raw CXType
  operator CXType() const;
  /// Get the type kind
  CXTypeKind kind() const;
  /// Get the type's name
  String spelling() const;
  /// Is the type const qualified ?
  bool is_const_qualified() const;
  /// Get the pointee type
  Type pointee_type() const;
};

class SourceRange {
  CXSourceRange _range;

 public:
  SourceRange() = delete;
  SourceRange(CXSourceRange range);
  SourceLocation start() const;
  SourceLocation end() const;
};

/// A libclang Cursor.
class Cursor {
  CXCursor _cursor;

 public:
  /// Create a null CXCursor
  Cursor();
  /// Create a Cursor from a CXCursor
  Cursor(CXCursor cursor);
  Cursor(Cursor const &cursor) = default;
  Cursor(Cursor &&cursor) = default;
  ~Cursor() = default;
  Cursor &operator=(Cursor const &cursor) = default;
  Cursor &operator=(Cursor &&cursor) = default;
  /// Get the raw CXCursor.
  operator CXCursor() const;
  /// Get the cursor's location
  SourceLocation location() const;
  /// Get the cursor's extent
  SourceRange extent() const;
  /// Get the cursor's name.
  String spelling() const;
  /// Get the cursor's kind.
  CursorKind kind() const;
  /// Get the cursor type
  Type type() const;
  /// Get the storage class of the cursor
  enum CX_StorageClass storage_class() const;
};

/// A libclang TranslationUnit.
class TranslationUnit {
  CXTranslationUnit _tunit;

 public:
  TranslationUnit() = delete;
  /// Create a translation unit from an index and a file path.
  TranslationUnit(Index &index, std::string const &filepath,
                  unsigned options = 0);
  /// Create a translation unit from the program arguments.
  TranslationUnit(Index &index, const char *const *argv, int argc,
                  unsigned options = 0);
  TranslationUnit(TranslationUnit const &unit) = delete;
  TranslationUnit(TranslationUnit &&unit) = default;
  /// Destroy a translation unit, and dispose of the underlying unit.
  ~TranslationUnit();
  TranslationUnit &operator=(TranslationUnit const &unit) = delete;
  TranslationUnit &operator=(TranslationUnit &&unit) = default;
  /// Get the raw CXTranslationUnit.
  operator CXTranslationUnit() const;
  /// Get the root cursor of the TranslationUnit.
  Cursor root() const;
};

enum class Result : int {
  Break = CXChildVisit_Break,
  Continue = CXChildVisit_Continue,
  Recurse = CXChildVisit_Recurse,
};

/// A visitor over a Cursor's AST.
class Visitor {
 public:
  void visit(Cursor const &cursor);
  CXChildVisitResult dispatch(Cursor const &cursor, Cursor const &parent);

#define KOUGAMI_VISITOR(name)                                   \
  virtual Result visit_##name(Cursor const &, Cursor const &) { \
    return Result::Recurse;                                     \
  }

  KOUGAMI_VISITOR(unexposed_decl)
  KOUGAMI_VISITOR(struct_decl)
  KOUGAMI_VISITOR(union_decl)
  KOUGAMI_VISITOR(class_decl)
  KOUGAMI_VISITOR(enum_decl)
  KOUGAMI_VISITOR(field_decl)
  KOUGAMI_VISITOR(enum_constant_decl)
  KOUGAMI_VISITOR(function_decl)
  KOUGAMI_VISITOR(var_decl)
  KOUGAMI_VISITOR(parm_decl)
  KOUGAMI_VISITOR(typedef_decl)
  KOUGAMI_VISITOR(type_ref)
  KOUGAMI_VISITOR(unary_operator)
  KOUGAMI_VISITOR(binary_operator)
  KOUGAMI_VISITOR(label_stmt)
  KOUGAMI_VISITOR(compound_stmt)
  KOUGAMI_VISITOR(switch_stmt)
  KOUGAMI_VISITOR(do_stmt)
  KOUGAMI_VISITOR(for_stmt)
  KOUGAMI_VISITOR(goto_stmt)
  KOUGAMI_VISITOR(indirect_goto_stmt)
  KOUGAMI_VISITOR(decl_stmt)
  KOUGAMI_VISITOR(macro_definition)
  KOUGAMI_VISITOR(inclusion_directive)
  KOUGAMI_VISITOR(unknown)

#undef KOUGAMI_VISITOR
};
}

#endif  // !KOUGAMI_CLANG_HPP
