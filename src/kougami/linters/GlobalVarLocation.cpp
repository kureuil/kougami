#include "kougami.hpp"

namespace kougami {
namespace linters {
Result GlobalVarLocation::visit_var_decl(Cursor const &cursor, Cursor const &) {
  this->check_cursor_is_in_source(cursor);
  return Result::Recurse;
}
}
}
