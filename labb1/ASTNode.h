//
// Created by Hanna Sjöström on 2025-03-04.
//

#ifndef LABB1_ASTNODE_H
#define LABB1_ASTNODE_H
#include <vector>
#include <memory>
#include <string>
#include "ASTNode.h"
#include "evaluate.h"

using ASTNodePtr = std::unique_ptr<struct ASTNode>;

struct ASTNode {
    virtual ~ASTNode() = default;
    virtual EvalResult evaluate(const std::string& input, size_t& index) = 0;
};

struct CONCATNode : public ASTNode{
    std::vector<ASTNodePtr> children;
    CONCATNode() = default;
    EvalResult evaluate(const std::string& input, size_t& index) override;
};

struct CHARNode : public ASTNode {
    char value;
    CHARNode(char val) : value(val) {}
    EvalResult evaluate(const std::string& input, size_t& index) override;
};

struct ORNode : public ASTNode {
    ASTNodePtr left;
    ASTNodePtr right;
    ORNode(ASTNodePtr lhs, ASTNodePtr rhs) : left(std::move(lhs)), right(std::move(rhs)) {};
    EvalResult evaluate(const std::string& input, size_t& index) override;
};

struct STARNode : public ASTNode {
    ASTNodePtr factor;
    STARNode(ASTNodePtr factor) : factor(std::move(factor)) {}
    EvalResult evaluate(const std::string& input, size_t& index) override;
};

struct GROUPNode : public ASTNode{
    ASTNodePtr expr;
    GROUPNode(ASTNodePtr expr) : expr(std::move(expr)){}
    EvalResult evaluate(const std::string& input, size_t& index) override;
};

struct ANYNode : public ASTNode {
    ANYNode() = default;
    EvalResult evaluate(const std::string& input, size_t& index) override;
};

struct COUNTNode : public ASTNode {
    ASTNodePtr factor;  // Faktorn som modifieras
    int count;          // Antalet upprepningar

    COUNTNode(ASTNodePtr factor, int count) : factor(std::move(factor)), count(count) {}
    EvalResult evaluate(const std::string& input, size_t& index) override;
};

#endif //LABB1_ASTNODE_H
