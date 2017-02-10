#include "clang.hpp"

namespace clang {
SourceRange::SourceRange(CXSourceRange range) : _range{range} {}

SourceLocation SourceRange::start() const {
  return clang_getRangeStart(_range);
}

SourceLocation SourceRange::end() const { return clang_getRangeEnd(_range); }
}
