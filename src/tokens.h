#ifndef TOKENS_H
#define TOKENS_H

#include <string>

enum class Tok {
    INT, IDENT, IF, NUMBER,
    EQEQ, ASSIGN, PLUS, MINUS,
    LPAREN, RPAREN, LBRACE, RBRACE,
    SEMI, END, UNKNOWN
};

struct Token {
    Tok type;
    std::string text;
    int num;
    size_t pos;
    Token(Tok t=Tok::UNKNOWN, std::string s="", int n=0, size_t p=0)
        : type(t), text(std::move(s)), num(n), pos(p) {}
};

inline std::string tok_name(Tok t) {
    switch(t){
        case Tok::INT: return "INT";
        case Tok::IDENT: return "IDENT";
        case Tok::IF: return "IF";
        case Tok::NUMBER: return "NUMBER";
        case Tok::EQEQ: return "EQEQ";
        case Tok::ASSIGN: return "ASSIGN";
        case Tok::PLUS: return "PLUS";
        case Tok::MINUS: return "MINUS";
        case Tok::LPAREN: return "LPAREN";
        case Tok::RPAREN: return "RPAREN";
        case Tok::LBRACE: return "LBRACE";
        case Tok::RBRACE: return "RBRACE";
        case Tok::SEMI: return "SEMI";
        case Tok::END: return "END";
        default: return "UNKNOWN";
    }
}

#endif
