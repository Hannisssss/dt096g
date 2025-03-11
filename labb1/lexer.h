//
// Created by Hanna Sjöström on 2025-02-05.
//

#ifndef LABB1_LEXER_H
#define LABB1_LEXER_H

#include <iostream>
#include <string>

//global! kan använda TokenType::OR osv direkt
enum TokenType {
    OR,            // "+"
    STAR,          // "*"
    CHAR,          // Any character
    GROUP_START,   // "("
    GROUP_END,     // " )"
    ANY,           // "."
    COUNT_START,   // "{"
    COUNT_END,      // "}"
    IGNORE_CASE,   // "\I"
    OUTPUT,        // "\O{n}"
    DIGIT,          // A number (0-9)
    END_OF_INPUT   // End of input (EOF)
};

struct Token{ //readability moment
    TokenType type;
    char value;
};

using it = std::string::iterator;

class Lexer {
public:
    Lexer(it first, it last);

    Token getNextToken();

    std::vector<Token> collectTokens();
private:
    it current; // Håller koll på var vi är
    it last;    // Markerar slutet på input
};



#endif //LABB1_LEXER_H
