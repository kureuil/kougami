#include <set>

#include "kougami.hpp"

namespace kougami {
namespace linters {
Result BreakAfterControl::visit_compound_stmt(Cursor const &cursor,
                                              Cursor const &parent) {
  std::set<CXCursorKind> controls{CXCursor_IfStmt, CXCursor_SwitchStmt,
                                  CXCursor_WhileStmt, CXCursor_DoStmt,
                                  CXCursor_ForStmt};
  if (controls.count(parent.kind()) > 0) {
    if (cursor.location().line() == parent.location().line()) {
      this->_errors.emplace_back(
          Error{cursor.location(),
                "control structure must be followed by a line feed"});
    }
  }
  return Result::Recurse;
}
}
}
