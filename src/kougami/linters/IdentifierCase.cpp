#include <algorithm>

#include "kougami.hpp"

namespace kougami {
namespace linters {
void IdentifierCase::check_identifier_case(Cursor const &cursor) {
  std::string spelling{cursor.spelling()};
  std::string lowered;
  lowered.resize(spelling.size());
  std::transform(spelling.begin(), spelling.end(), lowered.begin(), ::tolower);
  if (spelling != lowered) {
    this->_errors.emplace_back(Error{cursor.location(),
                                     "identifier should only contain lowercase "
                                     "letters, numbers and underscores"});
  }
}

Result IdentifierCase::visit_function_decl(Cursor const &cursor,
                                           Cursor const &) {
  this->check_identifier_case(cursor);
  return Result::Recurse;
}

Result IdentifierCase::visit_var_decl(Cursor const &cursor, Cursor const &) {
  this->check_identifier_case(cursor);
  return Result::Recurse;
}

Result IdentifierCase::visit_parm_decl(Cursor const &cursor, Cursor const &) {
  this->check_identifier_case(cursor);
  return Result::Recurse;
}

Result IdentifierCase::visit_typedef_decl(Cursor const &cursor,
                                          Cursor const &) {
  this->check_identifier_case(cursor);
  return Result::Recurse;
}
}
}
