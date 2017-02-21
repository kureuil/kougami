#include "kougami.hpp"

namespace kougami {
namespace linters {
Result GlobalVarLocation::visit_var_decl(Cursor const &cursor, Cursor const &) {
  if (cursor.storage_class() == CX_SC_Extern || cursor.storage_class() == CX_SC_PrivateExtern) {
    this->check_cursor_is_in_header(cursor);
  } else {
    this->check_cursor_is_in_source(cursor);
  }
  return Result::Recurse;
}
}
}
