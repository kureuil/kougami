#include "kougami.hpp"

namespace kougami {
namespace linters {
Result ForStatement::visit_for_stmt(Cursor const &cursor, Cursor const &) {
  this->_errors.emplace_back(
      Error{cursor.location(), "for statements are not allowed"});
  return Result::Recurse;
}
}
}
