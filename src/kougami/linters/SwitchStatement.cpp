#include "kougami.hpp"

namespace kougami {
namespace linters {
Result SwitchStatement::visit_switch_stmt(Cursor const &cursor,
                                          Cursor const &) {
  this->_errors.emplace_back(
      Error{cursor.location(), "switch statements are not allowed"});
  return Result::Recurse;
}
}
}
