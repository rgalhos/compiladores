#include <iostream>
#include <math.h>
#include "lexical/token.cpp"

int test1()
{
    Token t(Lexeme::DEL_TERMINATOR, 40, 30);
    std::cout << t.to_string() << std::endl;

    Token t2(Lexeme::CONST_DOUBLE, 14, 5, 3.1516828690);
    std::cout << t2.to_string() << std::endl;

    Token t3(Lexeme::CONST_INT, 4, 65, -5413);
    std::cout << t3.to_string() << std::endl;

    Token t4(Lexeme::CONST_UINT, 154, 55, -1);
    std::cout << t4.to_string() << std::endl;

    Token t5(Lexeme::CONST_DOUBLE, 154, 55, 'a');
    std::cout << t5.to_string() << std::endl;

    Token t6(Lexeme::CONST_DOUBLE, 154, 55);
    std::cout << t6.to_string() << std::endl;

    return 0;
}