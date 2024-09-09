#include <ParserRuleContext.h>
#include <YQLLexer.h>
#include <YQLParser.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <antlr4-c3/CodeCompletionCore.hpp>
#include <cstdlib>
#include <utility/AntlrPipeline.hpp>
#include <utility/Collections.hpp>
#include <utility/Testing.hpp>

namespace c3::test {

struct YQLGrammar {
  using Lexer = YQLLexer;
  using Parser = YQLParser;
};

TEST(YQLTest, Select) {
  AntlrPipeline<YQLGrammar> pipeline("SELECT * FROM ");

  c3::CodeCompletionCore completion(&pipeline.parser);
  completion.debugOptions.showTransitions = false;
  completion.debugOptions.showDebugOutput = false;
  completion.debugOptions.showResult = true;

  pipeline.parser.sql_query();
  const auto candidates = completion.collectCandidates(1);
  ASSERT_EQ(candidates.tokens.size(), 34);
}

}  // namespace c3::test
