#include "kougami.hpp"

namespace kougami {
namespace linters {
Result GlobalVarName::visit_var_decl(Cursor const &cursor,
                                     Cursor const &parent) {
  if (parent.kind() == CXCursor_TranslationUnit) {
    std::string varname{cursor.spelling()};
    if (varname.substr(0, 2) != "g_") {
      this->_errors.emplace_back(
          Error{cursor.location(),
                "global variables names should be prefixed by `g_`"});
    }
  }
  return Result::Recurse;
}
}
}
