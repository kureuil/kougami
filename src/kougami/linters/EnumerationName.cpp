#include "kougami.hpp"

namespace kougami {
namespace linters {
Result EnumerationName::visit_enum_decl(Cursor const &cursor, Cursor const &) {
  std::string spelling{cursor.spelling()};
  if (spelling.substr(0, 2) != "e_") {
    this->_errors.emplace_back(Error{
        cursor.location(), "enumeration names should be prefixed by `e_`"});
  }
  return Result::Continue;
}
}
}
