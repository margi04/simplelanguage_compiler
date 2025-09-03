#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "tokens.h"

class Lexer {
    std::string src;
    size_t i;
public:
    Lexer(const std::string &s): src(s), i(0) {}
    std::vector<Token> tokenize();
};

#endif
