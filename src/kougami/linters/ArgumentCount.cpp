#include "kougami.hpp"

namespace kougami {
namespace linters {
Result ArgumentCount::visit_function_decl(Cursor const &cursor,
                                          Cursor const &) {
  if ((!clang_isFunctionTypeVariadic(cursor.type()) &&
       clang_Cursor_getNumArguments(cursor) > 4) ||
      (clang_isFunctionTypeVariadic(cursor.type()) &&
       clang_Cursor_getNumArguments(cursor) > 3)) {
    this->_errors.emplace_back(Error{
        cursor.location(), "functions cannot have more than 4 parameters"});
  }
  return Result::Recurse;
}
}
}
