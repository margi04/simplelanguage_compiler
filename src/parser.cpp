#include "parser.h"

Token Parser::peek(){ return pos<toks.size()?toks[pos]:Token(Tok::END,"",0,pos); }
Token Parser::eat(){ Token t=peek(); if(pos<toks.size()) pos++; return t; }
void Parser::expect(Tok t, const std::string &msg){
    Token got=peek();
    if(got.type!=t) throw std::runtime_error("Expected "+tok_name(t)+" at "+std::to_string(got.pos)+" "+msg);
    eat();
}

std::vector<Stmt*> Parser::parse_program(){
    std::vector<Stmt*> stmts;
    while(peek().type!=Tok::END){
        if(peek().type==Tok::INT) stmts.push_back(parse_decl());
        else stmts.push_back(parse_stmt());
    }
    return stmts;
}

Stmt* Parser::parse_decl(){
    expect(Tok::INT);
    Token t = eat();
    if(t.type!=Tok::IDENT) throw std::runtime_error("Expected identifier at decl");
    expect(Tok::SEMI);
    return new DeclStmt(t.text);
}

Stmt* Parser::parse_stmt(){
    Token t=peek();
    if(t.type==Tok::IDENT) return parse_assign();
    throw std::runtime_error("Unknown statement at "+std::to_string(t.pos));
}

Stmt* Parser::parse_assign(){
    Token t = eat();
    std::string var=t.text;
    expect(Tok::ASSIGN);
    Expr* e=parse_expr();
    expect(Tok::SEMI);
    return new AssignStmt(var,e);
}

Expr* Parser::parse_expr(){
    Expr* node=parse_term();
    while(peek().type==Tok::PLUS || peek().type==Tok::MINUS){
        Token t=eat();
        Expr* right=parse_term();
        char op=(t.type==Tok::PLUS)?'+':'-';
        node=new BinaryExpr(op,node,right);
    }
    return node;
}

Expr* Parser::parse_term(){
    Token t=peek();
    if(t.type==Tok::NUMBER){ eat(); return new NumberExpr(t.num); }
    if(t.type==Tok::IDENT){ eat(); return new VarExpr(t.text); }
    throw std::runtime_error("Unexpected token in term");
}
