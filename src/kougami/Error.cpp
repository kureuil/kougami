#include <sstream>

#include "kougami.hpp"

namespace kougami {
Error::Error(clang::SourceLocation const &location, std::string const &message)
    : _location{location}, _where{}, _what{message} {
  std::stringstream ss;
  ss << location;
  _where = ss.str();
}

clang::SourceLocation const &Error::location() const { return _location; }

std::string const &Error::where() const { return _where; }

std::string const &Error::what() const { return _what; }

std::ostream &operator<<(std::ostream &stream, Error const &error) {
  return stream << error.location() << ": " << error.what();
}
}
