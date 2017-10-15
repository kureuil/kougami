#include "kougami.hpp"

namespace kougami {
namespace linters {
Result TypedefName::visit_typedef_decl(Cursor const &cursor, Cursor const &) {
  std::string spelling{cursor.spelling()};
  if (spelling.substr(spelling.length() - 2, spelling.length()) != "_t") {
    this->_errors.emplace_back(
        Error{cursor.location(), "typedef'd names should be suffixed by `_t`"});
  }
  return Result::Recurse;
}
}
}
