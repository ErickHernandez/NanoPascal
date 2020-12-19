#include "parser.h"

void Parser::program()
{
    if(currToken == Token::KwProgram){
        currToken = lexer.getNextToken();
        if(currToken == Token::ID){
            currToken = lexer.getNextToken();
            if(currToken == Token::Semicolon){
                currToken = lexer.getNextToken();

                if(currToken == Token::KwVar)
                    variable_section();            

                while(currToken == Token::KwFunction || currToken == Token::KwProcedure)
                    subprogram_decl();

                if(currToken == Token::KwBegin){
                    currToken = lexer.getNextToken();

                    std::vector<Token> stmt = {Token::ID, Token::KwWrite, Token::KwWriteln, Token::KwRead, Token::KwIf, 
                        Token::KwWhile, Token::KwRepeat, Token::KwFor, Token::KwBreak, Token::KwContinue, Token::Semicolon};
                    
                    while(vector_contains(stmt, currToken))
                        statement();
                    
                    if(currToken == Token::KwEnd){
                        currToken = lexer.getNextToken();

                        if(currToken == Token::Period){
                            currToken = lexer.getNextToken();
                        } else
                            throw "Syntax Error: Missing period. Function: program";
                    } else
                        throw "Syntax Error: Missing 'end' keyword. Function: program";
                } else
                    throw "Syntax Error: Missing 'begin' keyword. Function: program";
            } else 
                throw "Syntax Error: Missing semicolon. Function: program";
        } else 
            throw "Syntax Error: Missing ID. Function: program";
    } else 
        throw "Syntax Error: Missing 'program' keyword. Function: program";
}

void Parser::variable_section()
{
    if(currToken == Token::KwVar){
        currToken = lexer.getNextToken();

        variable_decl();

        while(currToken == Token::ID)
            variable_decl();
       
    } else 
        throw "Syntax Error: Missing 'var' keyword. Function: variable_section";
}

void Parser::variable_decl()
{
    if(currToken == Token::ID){
        currToken = lexer.getNextToken();

        while(currToken == Token::Comma){
            currToken = lexer.getNextToken();
            
            if(currToken == Token::ID)
                currToken = lexer.getNextToken();
            else 
                throw "Syntax Error: Missing ID in variable list declaration. Function: variable_decl";
        }

        if(currToken == Token::Colon){
            currToken = lexer.getNextToken();

            type();

            if(currToken == Token::Semicolon)
                currToken = lexer.getNextToken();
            else
                throw "Syntax Error: Missing semicolon in variable declaration. Function: variable_decl";    
        } else {
            throw "Syntax Error: Missing colon in variable declaration. Function: variable_decl";
        }


    } else {
        throw "Syntax Error: Missing ID in variable declaration. Function: variable_decl";
    }
}

void Parser::type()
{
    std::vector<Token> types = {Token::KwInteger, Token::KwBoolean, Token::KwChar};

    if(vector_contains(types, currToken))
        currToken = lexer.getNextToken();
    else if(currToken == Token::KwArray)
        array_type();
    else
        throw "Syntax Error: Missing type. Function: type";
}

void Parser::array_type()
{
    if(currToken == Token::KwArray){
        currToken = lexer.getNextToken();
        if(currToken == Token::LBracket){
            currToken = lexer.getNextToken();
            if(currToken == Token::intConstant){
                currToken = lexer.getNextToken();
                if(currToken == Token::DPeriod){
                    currToken = lexer.getNextToken();
                    if(currToken == Token::intConstant){
                        currToken = lexer.getNextToken();
                        if(currToken == Token::RBracket){
                            currToken = lexer.getNextToken();
                            if(currToken == Token::KwOf){
                                currToken = lexer.getNextToken();
                                type();
                            } else 
                                throw "Syntax Error: Missing 'of' keyword. Function: array-type";
                        } else 
                            throw "Syntax Error: Missing right bracket. Function: array-type";
                    } else 
                        throw "Syntax Error: Missing (second) intConstant. Function: array-type";
                } else 
                    throw "Syntax Error: Missing double period operator. Function: array-type";
            } else 
                throw "Syntax Error: Missing (first) intConstant. Function: array-type";
        } else 
            throw "Syntax Error: Missing right bracket. Function: array-type";
    } else {
        throw "Syntax Error: Missing 'array' keyword. Function: array-type";
    }
}

void Parser::subprogram_decl()
{
    subprogram_header();
    
    if(currToken == Token::KwVar)
        variable_section();

    if(currToken == Token::KwBegin){
        currToken = lexer.getNextToken();
        
        std::vector<Token> stmt = {Token::ID, Token::KwWrite, Token::KwWriteln, Token::KwRead, Token::KwIf, 
            Token::KwWhile, Token::KwRepeat, Token::KwFor, Token::KwBreak, Token::KwContinue};
        
        while(vector_contains(stmt, currToken))
            statement();
        
        if(currToken == Token::KwEnd){
            currToken = lexer.getNextToken();

            if(currToken == Token::Semicolon)
                currToken = lexer.getNextToken();
            else 
                throw "Syntax Error: Missing semicolon. Function: subprogram_decl";
        } else 
            throw "Syntax Error: Missing 'end' keyword. Function: subprogram_decl";
    } else
        throw "Syntax Error: Missing 'begin' keyword. Function: subprogram_decl";
}

void Parser::subprogram_header()
{
    if(currToken == Token::KwFunction)
        function_header();
    else if (currToken == Token::KwProcedure)
        procedure_header();
    else 
        throw "Syntax Error: Missing 'function' or 'procedure' keyword. Function: subprogram_header";
}

void Parser::function_header()
{
    if(currToken == Token::KwFunction){
        currToken = lexer.getNextToken();
        if(currToken == Token::ID){
            currToken = lexer.getNextToken();
            if(currToken == Token::LParenthesis){
                currToken = lexer.getNextToken();
                if(currToken == Token::KwVar || currToken == Token::ID){
                    argument_decl();

                    while(currToken == Token::Semicolon){ 
                        currToken = lexer.getNextToken();
                        argument_decl();
                    }

                    if(currToken == Token::RParenthesis){
                        currToken = lexer.getNextToken();
                        if(currToken == Token::Colon){
                            currToken = lexer.getNextToken();
                            type();
                            if(currToken == Token::Semicolon){
                                currToken = lexer.getNextToken();
                            } else 
                                throw "Syntax Error: Missing semicolon. Function: function_header";
                        } else
                            throw "Syntax Error: Missing colon. Function: function_header";
                    } else
                        throw "Syntax Error: Missing right parenthesis. Function: function_header"; 
                } else
                    throw "Syntax Error: Missing ID or 'var' keyword. Function: function_header";
            }
        } else
            throw "Syntax Error: Missing ID. Function: function_header";
    } else
        throw "Syntax Error: Missing 'function' keyword. Function: function_header";
}

void Parser::procedure_header()
{
    if(currToken == Token::KwProcedure){
        currToken = lexer.getNextToken();
        if(currToken == Token::ID){
            currToken = lexer.getNextToken();
            if(currToken == Token::LParenthesis){
                currToken = lexer.getNextToken();
                if(currToken == Token::KwVar || currToken == Token::ID){
                    argument_decl();

                    while(currToken == Token::Semicolon){
                        currToken = lexer.getNextToken();
                        argument_decl();
                    }

                    if(currToken == Token::RParenthesis){
                        currToken = lexer.getNextToken();
                        
                        if(currToken == Token::Semicolon){
                            currToken = lexer.getNextToken();
                        } else 
                            throw "Syntax Error: Missing semicolon. Function: procedure_header";
                    } else
                        throw "Syntax Error: Missing right parenthesis. Function: procedure_header"; 
                } else
                    throw "Syntax Error: Missing ID or 'var' keyword. Function: procedure_header";
            }
        } else
            throw "Syntax Error: Missing ID. Function: procedure_header";
    } else
        throw "Syntax Error: Missing 'function' keyword. Function: procedure_header";
}

void Parser::argument_decl()
{
    if(currToken == Token::KwVar){
        currToken = lexer.getNextToken();
        if(currToken == Token::ID){
            if(currToken == Token::Colon){
                currToken = lexer.getNextToken();
                type();
            } else
                throw "Syntax Error: Missing colon. Function: argument_decl";
        } else 
            throw "Syntax Error: Missing ID. Function: argument_decl";

    } else if(currToken == Token::ID){
        currToken = lexer.getNextToken();
        if(currToken == Token::Colon){
                currToken = lexer.getNextToken();
                type();
            } else
                throw "Syntax Error: Missing colon. Function: argument_decl";
    } else 
        throw "Syntax Error: Missing ID or 'var' keyword. Function: argument_decl";
}

void Parser::statement()
{
    std::vector<Token> built_func = {Token::KwWrite, Token::KwWriteln, Token::KwRead};

    if(currToken == Token::ID){
        currToken = lexer.getNextToken();
        assign_or_subprogram_call();
        
        if(currToken == Token::Semicolon){
            currToken = lexer.getNextToken();
        } else 
            throw "Syntax Error: Missing semicolon (a_or_s). Function: statement";
        
    } else if (vector_contains(built_func, currToken)){
        builtin_func();
    }else if(currToken == Token::KwIf){
        currToken = lexer.getNextToken();
        expr();

        if(currToken == Token::KwThen){
            currToken = lexer.getNextToken();
            block();

            if(currToken == Token::KwElse){
                currToken = lexer.getNextToken();
                block();
            }
        } else 
            throw "Syntax Error: Missing 'then' keyword. Function: statement";

    } else if(currToken == Token::KwWhile){
        currToken = lexer.getNextToken();
        expr();

        if(currToken == Token::KwDo){
            currToken = lexer.getNextToken();
            block();
        } else 
            throw "Syntax Error: Missing 'do' keyword. Function: statement";

    } else if(currToken == Token::KwRepeat){
        currToken = lexer.getNextToken();
        block();

        if(currToken == Token::KwUntil){
            expr();

            if(currToken == Token::Semicolon){
                currToken = lexer.getNextToken();
            } else 
                throw "Syntax Error: Missing semicolon (repeat). Function: statement";
        } else 
            throw "Syntax Error: Missing 'until' keyword. Function: statement";

    } else if(currToken == Token::KwFor){
        currToken = lexer.getNextToken();
        
        if(currToken == Token::ID){
            currToken = lexer.getNextToken();

            if(currToken == Token::Assign){
                currToken = lexer.getNextToken();
                expr();

                if(currToken == Token::KwTo){
                    currToken = lexer.getNextToken();
                    expr();

                    if(currToken == Token::KwDo){
                        currToken = lexer.getNextToken();
                        block();
                    } else
                        throw "Syntax Error: Missing 'do' keyword. Function: statement";
                } else
                    throw "Syntax Error: Missing 'to' keyword. Function: statement";
            } else
                throw "Syntax Error: Missing assign operator. Function: statement";
        } else 
            throw "Syntax Error: Missing ID. Function: statement";

    } else if(currToken == Token::KwBreak){
        currToken = lexer.getNextToken();
        if(currToken == Token::Semicolon){
            currToken = lexer.getNextToken();
        } else 
            throw "Syntax Error: Missing semicolon (break). Function: statement";
    } else if(currToken == Token::KwContinue){
        currToken = lexer.getNextToken();
        if(currToken == Token::Semicolon){
            currToken = lexer.getNextToken();
        } else 
            throw "Syntax Error: Missing semicolon (continue). Function: statement";
    } else if(currToken == Token::Semicolon){
        currToken = lexer.getNextToken();
    } else
        throw "Syntax Error: invalid statement. Function: statement";
}

void Parser::block()
{
    std::vector<Token> stmt = {Token::ID, Token::KwWrite, Token::KwWriteln, Token::KwRead, Token::KwIf, 
                        Token::KwWhile, Token::KwRepeat, Token::KwFor, Token::KwBreak, Token::KwContinue};
                    
    if(vector_contains(stmt, currToken)){
        statement();
    } else if(currToken == Token::KwBegin){
        currToken == lexer.getNextToken();

        while(vector_contains(stmt, currToken))
            statement();
    } else 
        throw "Syntax Error: Missing statement or 'begin' keyword. Function: block";
}

void Parser::assign_or_subprogram_call()
{
    if(currToken == Token::LBracket){
        currToken = lexer.getNextToken();
        expr();

        if(currToken == Token::RBracket){
            currToken = lexer.getNextToken();

            if(currToken == Token::Assign){
                currToken = lexer.getNextToken();
                expr();
            } else 
                throw "Syntax Error: Missing assign operator. Function: assign_or_subprogram_call";
        } else 
            throw "Syntax Error: Missing right bracket. Function: assign_or_subprogram_call";

    } else if(currToken == Token::Assign){
        currToken = lexer.getNextToken();
        expr();

    } else if(currToken == Token::LParenthesis){
        currToken = lexer.getNextToken();
        expr();

        while(currToken == Token::Comma){
            currToken = lexer.getNextToken();
            expr();
        }

        if(currToken == Token::RParenthesis){
            currToken = lexer.getNextToken();
        } else 
            throw "Syntax Error: Missing right parenthesis. Function: assign_or_subprogram_call";
    } 
}

void Parser::argument()
{
    std::vector<Token> expr_prefixes = {Token::ID, Token::KwWrite, Token::KwWriteln, Token::KwRead, Token::intConstant, Token::charConstant, 
            Token::KwTrue, Token::KwFalse, Token::Sub, Token::KwNot, Token::LParenthesis};

    if(currToken == Token::stringConstant){
        currToken = lexer.getNextToken();
        //return stringConstant
    } else if(vector_contains(expr_prefixes, currToken)){
        expr();
    } else 
        throw "Syntax Error: invalid argument. Function: argument";
    
}

void Parser::lvalue_or_subprogram_call()
{
    if(currToken == Token::LBracket){
        currToken = lexer.getNextToken();
        expr();

        if(currToken == Token::RBracket){
            currToken = lexer.getNextToken();
        } else 
            throw "Syntax Error: Missing right bracket. Function: lvalue_or_subprogram_call";

    } else if(currToken == Token::LParenthesis){
        currToken = lexer.getNextToken();
        expr();

        while(currToken == Token::Comma){
            currToken = lexer.getNextToken();
            expr();
        }

        if(currToken == Token::RParenthesis){
            currToken = lexer.getNextToken();
        } else
            throw "Syntax Error: Missing right parenthesis. Function: lvalue_or_subprogram_call";
    }
}

void Parser::builtin_func()
{
    if(currToken == Token::KwWrite){
        currToken = lexer.getNextToken();
        if(currToken == Token::LParenthesis){
            currToken = lexer.getNextToken();
            argument();

            while (currToken == Token::Comma){
                currToken = lexer.getNextToken();
                argument();
            }

            if(currToken == Token::RParenthesis){
                currToken = lexer.getNextToken();
            } else
                throw "Syntax Error: Missing right parenthesis (write func). Function: builtin_func";
            
        } else
            throw "Syntax Error: Missing left parenthesis (write func). Function: builtin_func";
    } else if(currToken == Token::KwWriteln){
        currToken = lexer.getNextToken();
        if(currToken == Token::LParenthesis){
            currToken = lexer.getNextToken();

            std::vector<Token> args = {Token::stringConstant, Token::intConstant, Token::KwTrue, Token::KwFalse, Token::KwWrite, 
                Token::KwWriteln, Token::KwRead, Token::ID, Token::Sub, Token::KwNot, Token::LParenthesis};

            if(vector_contains(args, currToken)){
                argument();
                
                while(currToken == Token::Comma){
                    currToken = lexer.getNextToken();
                    argument();
                }
            }

            if(currToken == Token::RParenthesis){
                currToken = lexer.getNextToken();
            } else 
                throw "Syntax Error: Missing right parenthesis (writeln func). Function: builtin_func";
        } else 
            throw "Syntax Error: Missing left parenthesis (writeln func). Function: builtin_func";
    } else if(currToken == Token::KwRead){
        currToken = lexer.getNextToken();

        if(currToken == Token::LParenthesis){
            currToken = lexer.getNextToken();

            argument();

            while (currToken == Token::Comma){
                currToken = lexer.getNextToken();
                argument();
            }

            if(currToken == Token::RParenthesis){
                currToken = lexer.getNextToken();
            } else
                throw "Syntax Error: Missing right parenthesis (read func). Function: builtin_func";

        } else
            throw "Syntax Error: Missing left parenthesis (read func). Function: builtin_func";
    }
}

void Parser::expr()
{

    std::vector<Token> builtin_funcs = {Token::KwWrite, Token::KwWriteln, Token::KwRead};
    std::vector<Token> constants = {Token::intConstant, Token::charConstant, Token::KwTrue, Token::KwFalse};
    std::vector<Token> bin_ops = {Token::Add, Token::Sub, Token::Mul, Token::KwDiv, Token::KwMod, Token::KwShl, Token::KwShr, 
        Token::LessThan, Token::GreaterThan, Token::LessOrEqual, Token::GreaterOrEqual, Token::Equal, Token::Distinct, 
        Token::KwAnd, Token::KwOr, Token::KwXor};


    if (currToken == Token::ID){
        currToken = lexer.getNextToken();
        lvalue_or_subprogram_call();

        if(vector_contains(bin_ops, currToken)){
            expr_bin_op();
        }

    } else if(vector_contains(builtin_funcs, currToken)){
        builtin_func();

        if(vector_contains(bin_ops, currToken)){
            expr_bin_op();
        }

    } else if(vector_contains(constants, currToken)){
        constant();

        if(vector_contains(bin_ops, currToken)){
            expr_bin_op();
        }

    } else if(currToken == Token::Sub){
        currToken = lexer.getNextToken();
        expr();

        if(vector_contains(bin_ops, currToken)){
            expr_bin_op();
        }

    } else if(currToken == Token::KwNot){
        currToken = lexer.getNextToken();
        expr();

        if(vector_contains(bin_ops, currToken)){
            expr_bin_op();
        }

    } else if(currToken == Token::LParenthesis){
        currToken = lexer.getNextToken();
        expr();

        if(currToken == Token::RParenthesis){
            currToken = lexer.getNextToken();
        } else 
            throw "Syntax Error: Missing right parenthesis. Function: expr";


        if(vector_contains(bin_ops, currToken)){
            expr_bin_op();
        }
    } else 
        throw "Syntax Error: No expression detected. Function: expr";
    
}

void Parser::expr_bin_op()
{
    bin_op();
    expr();
}

void Parser::bin_op()
{
    std::vector<Token> math = {Token::Add, Token::Sub, Token::Mul, Token::KwDiv, Token::KwMod, Token::KwShl, Token::KwShr};
    std::vector<Token> rel = {Token::LessThan, Token::GreaterThan, Token::LessOrEqual, Token::GreaterOrEqual};
    std::vector<Token> eq = {Token::Equal, Token::Distinct};
    std::vector<Token> cond = {Token::KwAnd, Token::KwOr, Token::KwXor};

    if(vector_contains(math, currToken)){
        arith_op();
    } else if(vector_contains(rel, currToken)){
        rel_op();
    } else if(vector_contains(eq, currToken)){
        eq_op();
    } else if(vector_contains(cond, currToken)){
        cond_op();
    }
}

void Parser::arith_op()
{
    std::vector<Token> op = {Token::Add, Token::Sub, Token::Mul, Token::KwDiv, Token::KwMod, Token::KwShl, Token::KwShr};

    if(vector_contains(op, currToken))
        currToken = lexer.getNextToken();
}

void Parser::rel_op()
{
    std::vector<Token> op = {Token::LessThan, Token::GreaterThan, Token::LessOrEqual, Token::GreaterOrEqual};

    if(vector_contains(op, currToken))
        currToken = lexer.getNextToken();
}

void Parser::eq_op()
{
    std::vector<Token> op = {Token::Equal, Token::Distinct};

    if(vector_contains(op, currToken))
        currToken = lexer.getNextToken();
}

void Parser::cond_op()
{
    std::vector<Token> op = {Token::KwAnd, Token::KwOr, Token::KwXor};

    if(vector_contains(op, currToken))
        currToken = lexer.getNextToken();
}

void Parser::constant()
{
    std::vector<Token> consts = {Token::intConstant, Token::charConstant};
    std::vector<Token> bools = {Token::KwTrue, Token::KwFalse};

    if(vector_contains(consts, currToken))
        currToken = lexer.getNextToken();
    else if(vector_contains(bools, currToken))
        bool_constant();
}

void Parser::bool_constant()
{
    std::vector<Token> consts = {Token::KwTrue, Token::KwFalse};

    if(vector_contains(consts, currToken))
        currToken = lexer.getNextToken();
}

bool Parser::vector_contains(std::vector<Token> list, Token value)
{
    if(std::find(list.begin(), list.end(), value) != list.end())
        return true;
    else
        return false;
}