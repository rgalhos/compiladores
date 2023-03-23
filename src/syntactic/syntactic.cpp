#ifndef SYNTACTIC_CPP
#define SYNTACTIC_CPP

#include <iostream>
#include <list>
#include "../lexical/token.cpp"

using namespace std;

list<Token> tokenList;

int syntatic_analyser(list<Token> _tokenList)
{
    tokenList = _tokenList;

    for (Token t : tokenList)
    {
        cout << t.to_string() << endl;
    }

    return 0;
}

#endif
