#include "kougami.hpp"

namespace kougami {
namespace linters {
Result RelativeInclusionDirective::visit_inclusion_directive(
    Cursor const &cursor, Cursor const &) {
  std::string spelling{cursor.spelling()};
  if (spelling.find("..") != std::string::npos ||
      spelling.find("./") != std::string::npos) {
    this->_errors.emplace_back(
        Error{cursor.location(), "Include shouldn't be relative paths"});
  }
  return Result::Recurse;
}
}
}
