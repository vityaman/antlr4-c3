#include "YQLLexer.h"
#include "YQLParser.h"

//

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "antlr4-c3/CodeCompletionCore.hpp"
#include "utility/AntlrPipeline.hpp"
#include "utility/Collections.hpp"
#include "utility/Testing.hpp"

namespace c3::test {

struct YQLGrammar {
  using Lexer = YQLLexer;
  using Parser = YQLParser;
};

TEST(YQLParser, CandidatesAfterSelect) {
  const auto* source = "SELECT ";
  AntlrPipeline<YQLGrammar> pipeline(source);

  CodeCompletionCore completion(&pipeline.parser);

  completion.debugOptions = {
      .showResult = true,
      .showDebugOutput = true,
      .showTransitions = true,
      .showRuleStack = true,
  };

  const auto& vocabulary = pipeline.lexer.getVocabulary();
  for (size_t type = 1; type <= vocabulary.getMaxTokenType(); ++type) {
    if (YQLGrammar::Lexer::ABORT <= type && type <= YQLGrammar::Lexer::XOR) {
      continue;
    }
    completion.ignoredTokens.emplace(type);
  }

  completion.preferredRules = {
      YQLGrammar::Parser::RuleKeyword,
      YQLGrammar::Parser::RuleKeyword_expr_uncompat,
      YQLGrammar::Parser::RuleKeyword_table_uncompat,
      YQLGrammar::Parser::RuleKeyword_select_uncompat,
      YQLGrammar::Parser::RuleKeyword_alter_uncompat,
      YQLGrammar::Parser::RuleKeyword_in_uncompat,
      YQLGrammar::Parser::RuleKeyword_window_uncompat,
      YQLGrammar::Parser::RuleKeyword_hint_uncompat,
      YQLGrammar::Parser::RuleKeyword_as_compat,
      YQLGrammar::Parser::RuleKeyword_compat,
  };

  pipeline.tokens.fill();

  size_t filteredCandidatesSize = 0;
  auto candidates = completion.collectCandidates(1);

  for (const auto& [token, following] : candidates.tokens) {
    const auto isFound = [&](auto ruleIndex) {  //
      const auto& rules = candidates.rules[token].ruleList;
      return std::ranges::find(rules, ruleIndex) != std::end(rules);
    };

    if (isFound(YQLGrammar::Parser::RuleKeyword) &&
        isFound(YQLGrammar::Parser::RuleKeyword_expr_uncompat) &&
        isFound(YQLGrammar::Parser::RuleKeyword_table_uncompat) &&
        isFound(YQLGrammar::Parser::RuleKeyword_select_uncompat) &&
        isFound(YQLGrammar::Parser::RuleKeyword_alter_uncompat) &&
        isFound(YQLGrammar::Parser::RuleKeyword_in_uncompat) &&
        isFound(YQLGrammar::Parser::RuleKeyword_window_uncompat) &&
        isFound(YQLGrammar::Parser::RuleKeyword_hint_uncompat) &&
        isFound(YQLGrammar::Parser::RuleKeyword_as_compat) &&
        isFound(YQLGrammar::Parser::RuleKeyword_compat)) {
      continue;
    }

    filteredCandidatesSize += 1;
  }

  EXPECT_THAT(filteredCandidatesSize, 30);
}

}  // namespace c3::test
