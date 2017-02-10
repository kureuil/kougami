#include <stdexcept>

#include "clang.hpp"

namespace clang {
File::File(CXFile file) : _file{file} {}

File::operator CXFile() const { return _file; }

String File::name() const { return clang_getFileName(_file); }

bool File::operator==(File const &rhs) const {
  return clang_File_isEqual(_file, rhs._file);
}

bool File::operator!=(File const &rhs) const {
  return !clang_File_isEqual(_file, rhs._file);
}

// bool File::is_multiple_include_guarded() const {
//   return clang_isFileMultipleIncludeGuarded(_file) != 0;
// }
}
