#include "kougami.hpp"

namespace kougami {
namespace linters {
Result TypedefOverStruct::visit_typedef_decl(Cursor const &cursor,
                                             Cursor const &) {
  std::string spelling{cursor.spelling()};
  clang::Type underlying{clang_getTypedefDeclUnderlyingType(cursor)};
  std::string underlying_spelling{underlying.spelling()};
  if (underlying.kind() == CXType_Unexposed &&
      underlying_spelling.substr(0, 9) == "struct s_") {
    if (underlying_spelling.substr(9) != spelling.substr(2)) {
      this->_errors.emplace_back(
          Error{cursor.location(),
                "typedef over a structure should have the same name"});
    }
  }
  return Result::Recurse;
}
}
}
