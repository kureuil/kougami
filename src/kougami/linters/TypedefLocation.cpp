#include "kougami.hpp"

namespace kougami {
namespace linters {
Result TypedefLocation::visit_typedef_decl(Cursor const &cursor,
                                           Cursor const &) {
  this->check_cursor_is_in_header(cursor);
  return Result::Recurse;
}
}
}
