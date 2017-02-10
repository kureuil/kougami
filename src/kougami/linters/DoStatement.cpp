#include "kougami.hpp"

namespace kougami {
namespace linters {
Result DoStatement::visit_do_stmt(Cursor const &cursor, Cursor const &) {
  this->_errors.emplace_back(
      Error{cursor.location(), "do...while statements are not allowed"});
  return Result::Recurse;
}
}
}
