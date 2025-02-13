//
// Created by Hanna Sjöström on 2025-02-05.
//

#ifndef LABB1_LEXER_H
#define LABB1_LEXER_H

#include <iostream>


// <REGEXPR> -> <EXPR>
// <EXPR> -> <OR> | <STAR> | <CAPTURE_GROUP> | <ANY> | <COUNT> | <IGNORE_CASE> | <OUTPUT> | <TERM>
// <OR> -> <TERM> + <TERM>
// <STAR> -> <TERM> *
// <CAPTURE_GROUP> -> ( <EXPR> )
// <ANY> -> .
// <COUNT> -> <TERM> {  <NUMBER>  } |  <ANY>  {  <NUMBER>  }
// <IGNORE_CASE> -> <TERM> \I
// <OUTPUT> -> <TERM> \O{ <NUMBER> }
// <TERM> -> <CHAR> [<TERM>]
// <CHAR> -> any non-special character
// <DIGIT> -> 0|1|2|3|4|5|6|7|8|9
// <NUMBER> -> <DIGIT> [<NUMBER>]

/*
 *
 *
 */
using it = std::string::iterator;

class lexer {
    enum token{
        REGEXP,
        EXPR,
        CHAR,
        INVALID,
        EOI
    };
};



#endif //LABB1_LEXER_H
