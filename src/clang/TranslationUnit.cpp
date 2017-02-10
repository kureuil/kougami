#include <stdexcept>

#include "clang.hpp"

namespace clang {
TranslationUnit::TranslationUnit(Index &index, std::string const &filepath,
                                 unsigned options)
    : _tunit{nullptr} {
  _tunit = clang_parseTranslationUnit(index, filepath.c_str(), nullptr, 0,
                                      nullptr, 0, options);
  if (!_tunit) {
    throw std::runtime_error{"Couldn't initialize CXTranslationUnit"};
  }
}

TranslationUnit::TranslationUnit(Index &index, char const *const *argv,
                                 int argc, unsigned options)
    : _tunit{nullptr} {
  _tunit = clang_parseTranslationUnit(index, nullptr, argv, argc, nullptr, 0,
                                      options);
  if (!_tunit) {
    throw std::runtime_error{"Couldn't initialize CXTranslationUnit"};
  }
}

TranslationUnit::~TranslationUnit() { clang_disposeTranslationUnit(_tunit); }

TranslationUnit::operator CXTranslationUnit() const { return _tunit; }

Cursor TranslationUnit::root() const {
  return clang_getTranslationUnitCursor(_tunit);
}
}
