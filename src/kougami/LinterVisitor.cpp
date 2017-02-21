#include <algorithm>
#include <iostream>
#include <set>

#include "kougami.hpp"

namespace kougami {
using clang::Cursor;

std::vector<Error> const &LinterVisitor::errors() const {
  return this->_errors;
}

void LinterVisitor::check_cursor_is_in_header(Cursor const &cursor) {
  std::string location{cursor.location().file().name()};
  if (location.substr(location.size() - 2, 2) != ".h") {
    this->_errors.emplace_back(
        Error{cursor.location(), "should be defined in a header"});
  }
}

void LinterVisitor::check_cursor_is_in_source(Cursor const &cursor) {
  std::string location{cursor.location().file().name()};
  if (location.substr(location.size() - 2, 2) != ".c") {
    this->_errors.emplace_back(
        Error{cursor.location(), "should be defined in a source file"});
  }
}

Result LinterVisitor::visit_var_decl(Cursor const &cursor,
                                     Cursor const &parent) {
  {
    std::cerr << cursor.location() << ": {var} " << cursor.spelling()
              << " from " << parent.spelling() << " ("
              << parent.kind().spelling() << ")" << std::endl;
  }
  return Result::Recurse;
}

Result LinterVisitor::visit_decl_stmt(Cursor const &cursor, Cursor const &) {
  std::cerr << cursor.location() << ": {decl} " << cursor.spelling()
            << std::endl;
  return Result::Recurse;
}

Result LinterVisitor::visit_unknown(Cursor const &cursor, Cursor const &) {
  std::cerr << "Encountered unknown CursorKind "
            << static_cast<CXCursorKind>(cursor.kind()) << " ("
            << cursor.kind().spelling() << ") in " << cursor.location()
            << std::endl;
  return Result::Recurse;
}
}
