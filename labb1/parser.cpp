//
// Created by Hanna Sjöström on 2025-02-05.
//

#include "parser.h"

Token Parser::current_token() {
    if (currentIndex < tokens.size()){
        return tokens[currentIndex];
    }
    return { TokenType::END_OF_INPUT, '\0' };
}

void Parser::next_token() {
    if (currentIndex < tokens.size()) {
        currentIndex++;
    }
}

bool Parser::is_unary_token(TokenType type) {
    return (
            type == TokenType::STAR ||      // *
            type == TokenType::COUNT_START ||    // {
            type == TokenType::IGNORE_CASE // \I
    );
}

int Parser::parse_digits() {
    int result = 0;
    bool hasDigits = false;

    while(current_token().type == TokenType::DIGIT){
        hasDigits = true;
        int digit = current_token().value - '0';
        result = result * 10 + digit;
        next_token();
    }
    if(!hasDigits){
        throw std::runtime_error("Expected a number");
    }
    return result;
}

ASTNodePtr Parser::parse() {
    return parse_expr();
}

ASTNodePtr Parser::parse_expr() {
    auto left = parse_term();
    while(current_token().type == TokenType::OR){ //kan finnas typ a|b|c
        next_token();
        auto right = parse_term();
        left = std::make_unique<ORNode>(std::move(left), std::move(right));
    }
    return left;
}

ASTNodePtr Parser::parse_term() {
    std::vector<ASTNodePtr> factors;
    factors.push_back(parse_factor());

    while (current_token().type != TokenType::OR &&
            current_token().type != TokenType::GROUP_END &&
            current_token().type != TokenType::END_OF_INPUT) {
        factors.push_back(parse_factor());
    }
    // Skapa EN CONCATNode med alla barn
    if (factors.size() == 1) {
        return std::move(factors[0]);
    } else {
        auto concatNode = std::make_unique<CONCATNode>();
        concatNode->children = std::move(factors);
        return concatNode;
    }
}

ASTNodePtr Parser::parse_factor() { //Atomära enhter
    ASTNodePtr node;
    if(current_token().type == TokenType::ANY){
        node = std::make_unique<ANYNode>();
        next_token();
    }else if(current_token().type == TokenType::GROUP_START){
        node = parse_group();
    }else if(current_token().type == TokenType::CHAR){
        node = std::make_unique<CHARNode>(current_token().value);
        next_token();
    }else{
        throw std::runtime_error("Unexpected token in factor: ");
    }

    while(is_unary_token(current_token().type)){
        node = parse_unary(std::move(node));
    }

    return node;
}

ASTNodePtr Parser::parse_unary(ASTNodePtr node) {
    if(current_token().type == TokenType::STAR){
        next_token();
        return std::make_unique<STARNode>(std::move(node));
    }else if(current_token().type == TokenType::COUNT_START){
        next_token();
        int count = parse_digits();
        if (current_token().type != TokenType::COUNT_END) {
            throw std::runtime_error("Expected '}' after count modifier");
        }
        next_token();
        return std::make_unique<COUNTNode>(std::move(node), count);
    }
    return node;
}

ASTNodePtr Parser::parse_group() {
    next_token();
    ASTNodePtr node = parse_expr();
    if(current_token().type != TokenType::GROUP_END){
        throw std::runtime_error("Expected ')' to end the group");
    }
    next_token();
    return std::make_unique<GROUPNode>(std::move(node));
}







