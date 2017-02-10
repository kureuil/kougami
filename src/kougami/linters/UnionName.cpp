#include "kougami.hpp"

namespace kougami {
namespace linters {
Result UnionName::visit_union_decl(Cursor const &cursor, Cursor const &) {
  std::string spelling{cursor.spelling()};
  if (spelling.substr(0, 2) != "u_") {
    this->_errors.emplace_back(
        Error{cursor.location(), "union names should be prefixed by `u_`"});
  }
  return Result::Recurse;
}
}
}
