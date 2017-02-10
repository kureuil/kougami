#include "kougami.hpp"

namespace kougami {
namespace linters {
Result StructureName::visit_struct_decl(Cursor const &cursor, Cursor const &) {
  std::string spelling{cursor.spelling()};
  if (spelling.substr(0, 2) != "s_") {
    this->_errors.emplace_back(
        Error{cursor.location(), "struct names should be prefixed by `s_`"});
  }
  return Result::Recurse;
}
}
}
