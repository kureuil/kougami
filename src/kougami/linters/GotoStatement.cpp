#include "kougami.hpp"

namespace kougami {
namespace linters {
Result GotoStatement::visit_label_stmt(Cursor const &cursor, Cursor const &) {
  this->_errors.emplace_back(
      Error{cursor.location(), "label statements are not allowed"});
  return Result::Recurse;
}

Result GotoStatement::visit_goto_stmt(Cursor const &cursor, Cursor const &) {
  this->_errors.emplace_back(
      Error{cursor.location(), "goto statements are not allowed"});
  return Result::Recurse;
}

Result GotoStatement::visit_indirect_goto_stmt(Cursor const &cursor,
                                               Cursor const &parent) {
  return this->visit_goto_stmt(cursor, parent);
}
}
}
