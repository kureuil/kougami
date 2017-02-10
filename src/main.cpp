#include <algorithm>
#include <iostream>

#include "kougami.hpp"

using namespace kougami;
using namespace kougami::linters;

const std::vector<Rule> rules = {
    {RuleKind::Error, 1, []() { return std::make_unique<IdentifierCase>(); }},
    {RuleKind::Error, 2, []() { return std::make_unique<StructureName>(); }},
    {RuleKind::Error, 3, []() { return std::make_unique<UnionName>(); }},
    {RuleKind::Error, 4, []() { return std::make_unique<EnumerationName>(); }},
    {RuleKind::Error, 5, []() { return std::make_unique<SwitchStatement>(); }},
    {RuleKind::Error, 6, []() { return std::make_unique<ForStatement>(); }},
    {RuleKind::Error, 7, []() { return std::make_unique<DoStatement>(); }},
    {RuleKind::Error, 8, []() { return std::make_unique<GotoStatement>(); }},
    {RuleKind::Error, 9, []() { return std::make_unique<MacroCase>(); }},
    {RuleKind::Error, 10, []() { return std::make_unique<MacroLocation>(); }},
    {RuleKind::Error, 11, []() { return std::make_unique<TypedefLocation>(); }},
    {RuleKind::Error, 12, []() { return std::make_unique<NoStructCopy>(); }},
    {RuleKind::Error, 13,
     []() { return std::make_unique<GlobalVarLocation>(); }},
    {RuleKind::Error, 14, []() { return std::make_unique<GlobalVarName>(); }},
    {RuleKind::Error, 15, []() { return std::make_unique<ArgumentCount>(); }},
    {RuleKind::Error, 15, []() { return std::make_unique<FunctionCount>(); }},
    {RuleKind::Error, 16, []() { return std::make_unique<FunctionLength>(); }},
    {RuleKind::Error, 17,
     []() { return std::make_unique<NoMultilineMacro>(); }},
    {RuleKind::Error, 18,
     []() { return std::make_unique<BreakAfterControl>(); }},
    {RuleKind::Error, 19,
     []() { return std::make_unique<NoSpaceAfterUnary>(); }},
    {RuleKind::Error, 20,
     []() { return std::make_unique<SpaceAroundBinary>(); }},

    {RuleKind::Warning, 1,
     []() { return std::make_unique<RelativeInclusionDirective>(); }},
};

int main(int argc, const char **argv) {
  try {
    clang::Index index{};
    clang::TranslationUnit tu{index, argv + 1, argc - 1,
                              CXTranslationUnit_DetailedPreprocessingRecord};
    auto root{tu.root()};
    std::vector<Error> errors{};
    for (auto &&rule : rules) {
      auto linter{rule.factory()};
      linter->visit(root);
      errors.insert(std::end(errors), std::begin(linter->errors()),
                    std::end(linter->errors()));
    }
    std::sort(std::begin(errors), std::end(errors), [](Error const &lhs,
                                                       Error const &rhs) {
      if (static_cast<std::string>(lhs.location().file().name()) <
          static_cast<std::string>(rhs.location().file().name())) {
        return true;

      } else if (static_cast<std::string>(lhs.location().file().name()) >
                 static_cast<std::string>(rhs.location().file().name())) {
        return false;
      }
      if (lhs.location().line() < rhs.location().line()) {
        return true;
      } else if (lhs.location().line() > rhs.location().line()) {
        return false;
      }
      return lhs.location().column() < rhs.location().column();
    });
    for (auto &&error : errors) {
      std::cout << error << std::endl;
    }
  } catch (std::exception &e) {
    std::cerr << argv[0] << ": " << e.what() << std::endl;
    return 1;
  }
  return 0;
}
