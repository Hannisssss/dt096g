//
// Created by Hanna Sjöström on 2025-02-05.
//

#ifndef LABB1_PARSER_H
#define LABB1_PARSER_H

#include <vector>
#include <memory>
#include "lexer.h"
#include "ASTNode.h"

class Parser {
public:
    Parser(const std::vector<Token>& tokens) : tokens(tokens), currentIndex(0) {}
    ASTNodePtr parse();  // Startar parsningen och returnerar roten av AST-trädet


private:
    const std::vector<Token>& tokens; // Vektorn som innehåller tokens
    size_t currentIndex;              // Håller koll på aktuellt index

    Token current_token();
    void next_token();
    int parse_digits();
    bool is_unary_token(TokenType type);

    ASTNodePtr parse_expr();    // Hanterar OR (|)
    ASTNodePtr parse_term();    // Hanterar konkatenation
    ASTNodePtr parse_factor();  // Hanterar tecken, grupper och andra grundläggande element
    ASTNodePtr parse_unary(ASTNodePtr node); // Hanterar * {n} \I
    ASTNodePtr parse_group();   // Hanterar parentesuttryck ( <EXPR> )
};



#endif //LABB1_PARSER_H
