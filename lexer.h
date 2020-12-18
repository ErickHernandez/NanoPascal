#ifndef __LEXER_H__
#define __LEXER_H__

#include <iostream>
#include <string>
#include <istream>
#include "tokens.h"

class Lexer
{
public:
    Lexer(std::istream& input): input(input)
    {}

    std::string getText()
    { return text; }

    int getNextChar()
    { return input.get(); }

    void ungetChar(int ch)
    { input.unget(); }

    void reportError(int ch) 
    {
        std::cerr << "Error: Invalid character: '" << ch << "'\n";
    }

    bool isEqual(const std::string& a, const std::string& b);

    
    Token getNextToken();
    Token findKeyword(const std::string& str);
    Token getCharOrString(const std::string& str);
    static const char *tokenToString(Token tk);

private:
    std::string text;
    std::istream& input;
};

#endif