#include <algorithm>
#include <iostream>

#include "kougami.hpp"

namespace kougami {
namespace linters {
Result MacroCase::visit_macro_definition(Cursor const &cursor, Cursor const &) {
  std::string spelling{cursor.spelling()};
  std::string uppered;
  uppered.resize(spelling.size());
  std::transform(spelling.begin(), spelling.end(), uppered.begin(), ::toupper);
  if (spelling != uppered) {
    this->_errors.emplace_back(Error{cursor.location(),
                                     "macros should only contain uppercase "
                                     "letters, numbers and underscores"});
  }
  return Result::Recurse;
}
}
}
