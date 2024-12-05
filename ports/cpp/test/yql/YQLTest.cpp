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

  pipeline.tokens.fill();

  auto candidates = completion.collectCandidates(1);
  EXPECT_THAT(candidates.tokens.size(), 281);
}

}  // namespace c3::test
