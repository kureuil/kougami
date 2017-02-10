#include "clang.hpp"

namespace clang {
CursorKind::CursorKind(CXCursorKind kind) : _kind{kind} {}

bool CursorKind::operator==(CXCursorKind rhs) const { return _kind == rhs; }

bool CursorKind::operator!=(CXCursorKind rhs) const { return _kind != rhs; }

CursorKind::operator CXCursorKind() const { return _kind; }

String CursorKind::spelling() const {
  return clang_getCursorKindSpelling(_kind);
}
}
