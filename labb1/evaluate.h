//
// Created by Hanna Sjöström on 2025-03-10.
//

#ifndef LABB1_EVALUATE_H
#define LABB1_EVALUATE_H
#include <string>

struct EvalResult {
    bool status;
    std::string match;

    explicit EvalResult(bool s, std::string text = "") : status(s), match(std::move(text)) {}

    // Hjälpfunktioner!
    static EvalResult success(std::string text) {
        return EvalResult(true, std::move(text));
    }

    static EvalResult failure() {
        return EvalResult(false, "");
    }
};

#endif //LABB1_EVALUATE_H
