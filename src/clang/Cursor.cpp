#include "clang.hpp"

namespace clang {
Cursor::Cursor() : _cursor{clang_getNullCursor()} {}

Cursor::Cursor(CXCursor cursor) : _cursor{cursor} {}

Cursor::operator CXCursor() const { return _cursor; }

SourceLocation Cursor::location() const {
  return clang_getCursorLocation(_cursor);
}

SourceRange Cursor::extent() const { return clang_getCursorExtent(_cursor); }

String Cursor::spelling() const { return clang_getCursorSpelling(_cursor); }

CursorKind Cursor::kind() const { return clang_getCursorKind(_cursor); }

Type Cursor::type() const { return clang_getCursorType(_cursor); }

enum CX_StorageClass Cursor::storage_class() const {
  return clang_Cursor_getStorageClass(_cursor);
}
}
