#include <iostream>
#include <fstream>
#include "lexer.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input file>\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open())
    {
        std::cerr << "Cannot open '" << argv[1] << "'\n";
        return 1;
    }

    Lexer lexer(input);

    Token tk = lexer.getNextToken();

    while (tk != Token::EoF)
    {
        std::cout << "Token: " << Lexer::tokenToString(tk) << ", Lexema: " << lexer.getText() << '\n';
        tk = lexer.getNextToken();
    }
}