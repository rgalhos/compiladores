#ifndef SYNTACTIC_CPP
#define SYNTACTIC_CPP

#include <iostream>
#include <list>
#include "../lexical/token.cpp"

using namespace std;

void printBadToken(Token t);

list<Token> tokenList;

int syntatic_analyser(list<Token> _tokenList)
{
    tokenList = _tokenList;

    for (Token t : tokenList)
    {
        cout << t.to_string() << endl;

        if (t.lexeme == +Lexeme::UNKNOWN) {
            printBadToken(t);
        }
    }

    return 0;
}

void printBadToken(Token t) {
    cerr << "              \u001b[31m~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\033[0m" << endl;
    cerr << "              \u001b[31mErro:\033[0m Token inválido" << endl;
}

#endif
