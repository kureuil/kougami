#include "clang.hpp"

namespace clang {
Type::Type(CXType type) : _type{type} {}

Type::operator CXType() const { return _type; }

CXTypeKind Type::kind() const { return _type.kind; }

String Type::spelling() const { return clang_getTypeSpelling(_type); }

bool Type::is_const_qualified() const {
  return clang_isConstQualifiedType(_type);
}

Type Type::pointee_type() const { return clang_getPointeeType(_type); }
}
