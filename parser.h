#ifndef __PARSER_H__
#define __PARSER_H__

#include "lexer.h"

class Parser
{
public:
    Parser(Lexer& lexer):lexer(lexer)
    {}

    void parse()
    {
        currToken = lexer.getNextToken();

        program();

        if(currToken != Token::EoF){
            std::cout<<static_cast<int>(currToken);
            throw "Syntax Error. EoF expected!";
        }
    }

    Token getCurrentToken(){
        return currToken;
    }

private:

    Lexer& lexer;
    Token currToken;

    bool vector_contains(std::vector<Token> list, Token value);

    void program();
    void variable_section();
    void variable_decl();
    void type();
    void array_type();
    void subprogram_decl();
    void subprogram_header();
    void function_header();
    void procedure_header();
    void argument_decl();
    void statement();
    void block();
    void assign_or_subprogram_call();
    void argument();
    void lvalue_or_subprogram_call();
    void builtin_func();
    void expr();
    void expr_bin_op();
    void bin_op();
    void arith_op();
    void rel_op();
    void eq_op();
    void cond_op();
    void constant();
    void bool_constant();
    
};

#endif