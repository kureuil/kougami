#include "kougami.hpp"

namespace kougami {
namespace linters {
Result SpaceAroundBinary::visit_binary_operator(Cursor const &,
                                                Cursor const &) {
  return Result::Recurse;
}
}
}
