#include "codegen.h"

std::string CodeGen::generate(const std::vector<Stmt*>& prog){
    std::string out=";Generated code\n";
    for(auto s:prog){
        out+=s->repr()+"\n";
    }
    out+="HALT\n";
    return out;
}
