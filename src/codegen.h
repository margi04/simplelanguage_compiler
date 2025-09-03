#ifndef CODEGEN_H
#define CODEGEN_H

#include <vector>
#include <string>
#include "ast.h"

class CodeGen {
public:
    CodeGen(int start=0xF0){}
    std::string generate(const std::vector<Stmt*>& prog);
};

#endif
