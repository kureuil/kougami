#include "kougami.hpp"

namespace kougami {
namespace linters {
Result NoStructCopy::visit_parm_decl(Cursor const &cursor, Cursor const &) {
  std::string type_name{cursor.type().spelling()};
  // beautiful hack, cannot know if it's a struct, an enum or a union so first
  // we
  // check that its an unexposed type & check that its name start with
  // `struct `.
  if (cursor.type().kind() == CXType_Unexposed &&
      type_name.substr(0, 7) == "struct ") {
    this->_errors.emplace_back(
        Error{cursor.location(),
              "struct shouldn't be passed by copy, use a pointer"});
  }
  return Result::Recurse;
}
}
}
