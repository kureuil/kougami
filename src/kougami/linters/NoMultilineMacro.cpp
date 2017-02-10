#include "kougami.hpp"

namespace kougami {
namespace linters {
Result NoMultilineMacro::visit_macro_definition(Cursor const &cursor,
                                                Cursor const &) {
  if (cursor.extent().end().line() - cursor.extent().start().line() > 0) {
    this->_errors.emplace_back(
        Error{cursor.location(), "multiline macros are not allowed"});
  }
  return Result::Recurse;
}
}
}
