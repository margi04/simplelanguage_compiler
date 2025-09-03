#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <iostream>

struct Expr {
    virtual ~Expr() {}
    virtual std::string repr() const = 0;
};

struct NumberExpr : Expr {
    int value;
    NumberExpr(int v) : value(v) {}
    std::string repr() const override { return "Number(" + std::to_string(value) + ")"; }
};

struct VarExpr : Expr {
    std::string name;
    VarExpr(std::string n) : name(std::move(n)) {}
    std::string repr() const override { return "Var(" + name + ")"; }
};

struct BinaryExpr : Expr {
    char op;
    Expr* left;
    Expr* right;
    BinaryExpr(char o, Expr* l, Expr* r) : op(o), left(l), right(r) {}
    std::string repr() const override {
        return "Binary(" + std::string(1,op) + "," + left->repr() + "," + right->repr() + ")";
    }
};

struct Stmt {
    virtual ~Stmt() {}
    virtual std::string repr() const = 0;
};

struct DeclStmt : Stmt {
    std::string name;
    DeclStmt(std::string n) : name(std::move(n)) {}
    std::string repr() const override { return "Decl(" + name + ")"; }
};

struct AssignStmt : Stmt {
    std::string var;
    Expr* value;
    AssignStmt(std::string v, Expr* e) : var(std::move(v)), value(e) {}
    std::string repr() const override { return "Assign(" + var + "," + value->repr() + ")"; }
};

struct IfStmt : Stmt {
    Expr* left;
    Expr* right;
    std::vector<Stmt*> block;
    IfStmt(Expr* l, Expr* r) : left(l), right(r) {}
    std::string repr() const override {
        return "If(" + left->repr() + "==" + right->repr() + ")";
    }
};

#endif
