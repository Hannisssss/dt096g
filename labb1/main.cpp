
#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "print.h"
#include "evaluate.h"

int main() {
    //std::string input = "Wat";
    std::string input = "Waterloo I was defeated, you won the war Waterloo promise to"
                        " love you for ever more Waterloo couldn't escape if I wanted"
                        " to Waterloo knowing was my fate is I to be with you Waterloo finally"
                        " facing my Waterloo ";

    std::string match= "could.{3}";
    Lexer lexer(match.begin(),match.end());
    std::vector<Token> tokens = lexer.collectTokens();
    Parser parser(tokens);
    ASTNodePtr rootNode = parser.parse();
    //printTree(rootNode);

    for (size_t start = 0; start < input.size(); start++) { //gå igenom alla startpunkter
        size_t index = start;
        EvalResult result = rootNode->evaluate(input, index);
        if (result.status) {
            std::cout << "Match: " << result.match;
            return EXIT_SUCCESS;
        }
    }
    std::cout << "Match not found\n";
    return EXIT_FAILURE;
}

