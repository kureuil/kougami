#include <iostream>

#include "kougami.hpp"

namespace kougami {
namespace linters {
Result NoSpaceAfterUnary::visit_unary_operator(Cursor const &cursor,
                                               Cursor const &) {
  // if (cursor.location().line())
  std::cerr << cursor.location() << ": {" << cursor.spelling() << "} " << cursor.extent().start().column()
            << "--" << cursor.extent().end().column() << std::endl;
  return Result::Recurse;
}
}
}
