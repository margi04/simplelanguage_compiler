#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "tokens.h"
#include "ast.h"
#include <stdexcept>

class Parser {
    std::vector<Token> toks;
    size_t pos;
public:
    Parser(std::vector<Token> t): toks(std::move(t)), pos(0) {}
    std::vector<Stmt*> parse_program();

private:
    Token peek();
    Token eat();
    void expect(Tok t, const std::string &msg="");
    Stmt* parse_stmt();
    Stmt* parse_decl();
    Stmt* parse_assign();
    Expr* parse_expr();
    Expr* parse_term();
};

#endif
