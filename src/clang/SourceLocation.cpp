#include "clang.hpp"

namespace clang {
SourceLocation::SourceLocation()
    : _location{clang_getNullLocation()},
      _file{nullptr},
      _line{0},
      _column{0},
      _offset{0} {}

SourceLocation::SourceLocation(CXSourceLocation location)
    : _location{location}, _file{nullptr}, _line{0}, _column{0}, _offset{0} {
  clang_getExpansionLocation(_location, &_file, &_line, &_column, &_offset);
}

SourceLocation::operator CXSourceLocation() const { return _location; }

File SourceLocation::file() const { return _file; }

unsigned SourceLocation::line() const { return _line; }

unsigned SourceLocation::column() const { return _column; }

bool SourceLocation::is_from_main_file() const {
  return clang_Location_isFromMainFile(_location);
}

bool SourceLocation::is_in_system_header() const {
  return clang_Location_isInSystemHeader(_location);
}

std::ostream &operator<<(std::ostream &stream, SourceLocation const &location) {
  if (static_cast<CXFile>(location.file()) == nullptr) {
    stream << "(null)";
  } else {
    stream << location.file().name();
  }
  return stream << ":" << location.line() << ":" << location.column();
}
}
