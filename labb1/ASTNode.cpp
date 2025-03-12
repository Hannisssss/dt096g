//
// Created by Hanna Sjöström on 2025-03-04.
//
#include "ASTNode.h"
#include <string>
EvalResult CONCATNode::evaluate(const std::string &input, size_t &index) {
    std::string match;

    for(auto &child: children){
        EvalResult child_result = child->evaluate(input,index);

        if(!child_result.status){
            return child_result;
        }
        match += child_result.match;
    }
    return EvalResult::success(match);
}

EvalResult CHARNode::evaluate(const std::string &input, size_t &index) {
    if(index < input.size() && input[index] == value){
        index++;
        return EvalResult::success(std::string(1, value));
    }
    return EvalResult::failure();
}

EvalResult ORNode::evaluate(const std::string &input, size_t &index) {
    EvalResult left_result = left->evaluate(input, index);
    if(left_result.status){
        return left_result;
    }
    EvalResult right_result = right->evaluate(input, index);
    if(right_result.status){
        return right_result;
    }
    return EvalResult::failure();
}

EvalResult STARNode::evaluate(const std::string &input, size_t &index) {
    std::string match;
    while(true){
        EvalResult result = factor->evaluate(input,index);
        if(!result.status){
            break;
        }
        match += result.match;
    }
    return EvalResult::success(match);
}

EvalResult GROUPNode::evaluate(const std::string &input, size_t &index) {
    EvalResult result = expr->evaluate(input,index);
    if(result.status){
        return result;
    }
    return EvalResult::failure();
}

EvalResult ANYNode::evaluate(const std::string &input, size_t &index) {
    if(index < input.size()){
        std::string match( 1,input[index]);
        index++;
        return EvalResult::success(match);
    }
    return EvalResult::failure();
}

EvalResult COUNTNode::evaluate(const std::string &input, size_t &index) {
    size_t original_index = index;
    std::string match;
    int i = 0;

    while(i < count){
    EvalResult result = factor->evaluate(input, index);
    if(!result.status){
        index = original_index;
        return result;
    }
    match += result.match;
    i++;
    }
    return EvalResult::success(match);
}


