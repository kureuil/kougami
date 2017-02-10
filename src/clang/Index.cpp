#include "clang.hpp"

namespace clang {
Index::Index() : _index{clang_createIndex(1, 0)} {}

Index::~Index() { clang_disposeIndex(_index); }

Index::operator CXIndex() const { return _index; }
}
