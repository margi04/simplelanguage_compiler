#include "lexer.h"
#include <cctype>
#include <stdexcept>

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (i < src.size()) {
        char c = src[i];
        if (isspace(c)) { i++; continue; }

        if (isdigit(c)) {
            int start = i;
            int num=0;
            while (i < src.size() && isdigit(src[i])) {
                num = num*10 + (src[i]-'0');
                i++;
            }
            tokens.emplace_back(Tok::NUMBER, std::to_string(num), num, start);
            continue;
        }

        if (isalpha(c)) {
            int start=i;
            std::string ident;
            while (i<src.size() && (isalnum(src[i])||src[i]=='_')) {
                ident+=src[i];
                i++;
            }
            if (ident=="int") tokens.emplace_back(Tok::INT, ident,0,start);
            else if (ident=="if") tokens.emplace_back(Tok::IF, ident,0,start);
            else tokens.emplace_back(Tok::IDENT, ident,0,start);
            continue;
        }

        switch(c){
            case '=': tokens.emplace_back(Tok::ASSIGN,"=",0,i); break;
            case '+': tokens.emplace_back(Tok::PLUS,"+",0,i); break;
            case '-': tokens.emplace_back(Tok::MINUS,"-",0,i); break;
            case '(': tokens.emplace_back(Tok::LPAREN,"(",0,i); break;
            case ')': tokens.emplace_back(Tok::RPAREN,")",0,i); break;
            case '{': tokens.emplace_back(Tok::LBRACE,"{",0,i); break;
            case '}': tokens.emplace_back(Tok::RBRACE,"}",0,i); break;
            case ';': tokens.emplace_back(Tok::SEMI,";",0,i); break;
            default: throw std::runtime_error("Unexpected char: "+std::string(1,c));
        }
        i++;
    }
    tokens.emplace_back(Tok::END,"",0,i);
    return tokens;
}
