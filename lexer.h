#ifndef __LEXER_H__
#define __LEXER_H__

#include <iostream>
#include <string>
#include <istream>
#include "tokens.h"
#include "vector"
#include <algorithm>

class Directive
{
public:
    Directive(std::string variable, std::string type, bool is_valid): variable(variable), type(type), is_valid(is_valid)
    {}

    std::string variable;
    std::string type;
    bool is_valid;
};

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
    
    Token getNextToken();
    Token findKeyword(const std::string& str);
    Token getCharOrString(const std::string& str);
    static const char *tokenToString(Token tk);

private:
    void ifdef_fn();
    void ifndef_fn();
    void else_fn();
    void endif_fn();
    bool vector_contains(std::vector<std::string> list, std::string value);
    bool isEqual(const std::string& a, const std::string& b);
    std::string parse_directive(std::string text);

    std::vector<std::string> defined_directives = {"NANOPASCAL"};
    std::vector<Directive> directives_stack;

    std::string text;
    std::istream& input;
};

#endif