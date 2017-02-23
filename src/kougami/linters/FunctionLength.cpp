#include <iostream>

#include "kougami.hpp"

namespace kougami {
namespace linters {
Result FunctionLength::visit_compound_stmt(Cursor const &cursor,
                                           Cursor const &parent) {
  if (parent.kind() != CXCursor_FunctionDecl) {
    return Result::Recurse;
  }
  if (cursor.extent().end().line() - cursor.extent().start().line() - 1 > 25) {
    this->_errors.emplace_back(
        Error{cursor.location(), "function must not be longer than 25 lines"});
  }
  return Result::Recurse;
}
}
}
