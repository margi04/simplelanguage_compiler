#include <iostream>
#include <fstream>
#include <sstream>

#include "lexer.h"
#include "parser.h" 
#include "codegen.h"


std::string slurp_file(const std::string &path){
    std::ifstream ifs(path);
    if(!ifs) throw std::runtime_error("Could not open file: "+path);
    std::stringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
}
 int main(int argc, char** argv){
    if(argc <2){
        std::cerr << "Usage: " << argv[0] << "[--tokens|--ast] <input.sl>\n";
    return 1;

    }
    std::string mode="gen";
    std::string infile;
    if(argc == 2) infile=argv[1];
    else {
        mode = argv[1];infile=argv[2];

 } 
try{
    std::string src=slurp_file(infile);
    Lexer lx(src);
    auto toks=lx.tokenize();
    if(mode == std::string("--tokens")){
        for(auto &t:toks){
            std::cout << tok_name(t.type);
            if(!t.text.empty()) std::cout << "('" << t.text << "')";
            if(t.type == Tok :: NUMBER) std::cout << "{" << t.num << "}";
            std::cout << " @ " << t.pos << "\n";
        }
        return 0;
}
Parser p(toks);
auto prog =p.parse_program();
if(mode == std::string("--ast")){
    for(auto s:prog){
        std::cout << s->repr() << "\n";
        for(auto s:prog) delete s;
    return 0;
    }

}
CodeGen cg(0xF0);
std::string asm_code=cg.generate(prog);
std::cout << asm_code;
for(auto s:prog) delete s;}
catch(std::exception &e){
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
}
return 0;
}   

