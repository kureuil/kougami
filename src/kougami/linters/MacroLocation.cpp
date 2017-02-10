#include <set>

#include "kougami.hpp"

namespace kougami {
namespace linters {
Result MacroLocation::visit_macro_definition(Cursor const &cursor,
                                             Cursor const &) {
  std::string spelling{cursor.spelling()};
  const std::set<std::string> allowed_macros{"_POSIX_C_SOURCE",
                                             "_XOPEN_SOURCE",
                                             "_GNU_SOURCE",
                                             "_DEFAULT_SOURCE",
                                             "__STRICT_ANSI__",
                                             "_POSIX_SOURCE",
                                             "_XOPEN_SOURCE_EXTENDED",
                                             "_ISOC99_SOURCE",
                                             "_ISOC11_SOURCE",
                                             "_LARGEFILE64_SOURCE",
                                             "_LARGEFILE_SOURCE",
                                             "_FILE_OFFSET_BITS",
                                             "_BSD_SOURCE",
                                             "_SVID_SOURCE",
                                             "_ATFILE_SOURCE",
                                             "_REENTRANT",
                                             "_THREAD_SAFE",
                                             "_FORTIFY_SOURCE"};
  if (allowed_macros.count(spelling) == 0) {
    this->check_cursor_is_in_header(cursor);
  }
  return Result::Recurse;
}
}
}
