#include "kougami.hpp"

namespace kougami {
namespace linters {
Result FunctionCount::visit_function_decl(Cursor const &cursor,
                                          Cursor const &) {
  std::string filename{cursor.location().file().name()};
  if (filename.substr(filename.size() - 2, 2) == ".c") {
    this->_files[filename].functions += 1;
    if (this->_files[filename].functions > 5) {
      this->_errors.emplace_back(Error{
          cursor.location(), "only 5 functions are allowed per source file"});
    }
  }
  return Result::Recurse;
}
}
}
