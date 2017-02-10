#include "clang.hpp"

namespace clang {
String::String(CXString string) : _string{string} {}

String::~String() { clang_disposeString(_string); }

char const *String::c_str() const { return clang_getCString(_string); }

String::operator std::string() const { return this->c_str(); }

std::ostream &operator<<(std::ostream &stream, String const &string) {
  return stream << string.c_str();
}
}
