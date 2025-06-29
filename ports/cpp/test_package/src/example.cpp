#include "expr/ExprParser.h"
#include "expr/ExprLexer.h"

#include "antlr4-runtime.h"
#include "antlr4-c3.hpp"

#include <vector>
#include <string>

int main() {
    const std::string input = "1 + 2 * 3";
    antlr4::ANTLRInputStream input_stream(input);
    ExprLexer lexer(&input_stream);
    antlr4::CommonTokenStream tokens(&lexer);
    ExprParser parser(&tokens);

    parser.prog();
    c3::CodeCompletionCore core(&parser);

    c3::CandidatesCollection candidates = core.collectCandidates(0);

    return 0;
}
