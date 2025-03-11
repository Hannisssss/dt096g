//
// Created by Hanna Sjöström on 2025-02-05.
//

#include "lexer.h"

Lexer::Lexer(it start, it end) : current(start), last(end) {}
Token Lexer::getNextToken() {
    if (current == last) {
        return { TokenType::END_OF_INPUT, '\0' };
    }

    char ch = *current;
    current++;

    switch (ch) {
        case '+': return { TokenType::OR, ch };
        case '*': return { TokenType::STAR, ch  };
        case '(': return { TokenType::GROUP_START, ch };
        case ')': return { TokenType::GROUP_END, ch  };
        case '.': return { TokenType::ANY, ch  };
        case '{': return { TokenType::COUNT_START, ch  };
        case '}': return { TokenType::COUNT_END, ch  };
        case '\\':  // Hantera escape-sekvenser \I och \O{}
            if (current != last) {
                char next = *current++;
                if (next == 'I') return { TokenType::IGNORE_CASE, ch  };
                if (next == 'O') return { TokenType::OUTPUT, ch  };
            }else {
                std::cerr << "invalid regex: Expected 'I' or 'O' after '/'." << std::endl;
            }

        default:
            if (isdigit(ch)) {
                return { TokenType::DIGIT, ch };
            }
            return { TokenType::CHAR, ch  };
    }
}

std::vector<Token> Lexer::collectTokens() {
    std::vector<Token> tokens;
    Token token = getNextToken();

    while(token.type != TokenType::END_OF_INPUT){
        tokens.push_back(token);
        token = getNextToken();
    }

    return tokens;
}
