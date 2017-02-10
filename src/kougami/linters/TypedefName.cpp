#include "kougami.hpp"

namespace kougami {
namespace linters {
Result TypedefName::visit_typedef_decl(Cursor const &cursor, Cursor const &) {
  std::string spelling{cursor.spelling()};
  if (spelling.substr(0, 2) != "t_") {
    this->_errors.emplace_back(
        Error{cursor.location(), "typedef'd names should be prefixed by `t_`"});
  }
  return Result::Recurse;
}
}
}
