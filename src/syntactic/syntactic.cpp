#ifndef SYNTACTIC_CPP
#define SYNTACTIC_CPP

#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include "../lexical/token.cpp"
#include "./constants.cpp"
#include "./parse_tables.cpp"

using namespace std;

void printBadToken(Token t);
int parseTokens();

vector<Token> tokenList;

vector<Production> productions;
ActionTableItem actionTable[NUM_STATES][NUM_TERMINALS];
int gotoTable[NUM_STATES][NUM_NON_TERMINALS];

int syntatic_analyser(vector<Token> _tokenList)
{
    tokenList = _tokenList;

    for (Token t : tokenList)
    {
        cout << t.to_string() << endl;

        if (t.lexeme == +Lexeme::UNKNOWN)
        {
            printBadToken(t);
        }
    }

    readProductions(&productions);
    readActionTable(actionTable);
    readGotoTable(gotoTable);

    return parseTokens();
}

int parseTokens()
{
    vector<Token> inputTokens(tokenList);

    inputTokens.push_back(Token(Lexeme::STOP, -1, -1));

    int head = 0;
    int currTerminal = lexeme_to_int(inputTokens[head].lexeme);

    stack<int> pilha;
    pilha.push(0);

    while (true)
    {
        int s = pilha.top();

        ActionTableItem item = actionTable[s][currTerminal];

        if (item.action == Action::SHIFT)
        {
            pilha.push(item.id);
            currTerminal = lexeme_to_int(inputTokens[++head].lexeme);
        }
        else if (item.action == Action::REDUCE)
        {
            for (int i = 0; i < productions[item.id - 1].rightSize; i++)
                pilha.pop();

            s = pilha.top();
            pilha.push(gotoTable[s][productions[item.id - 1].left]);
        }
        else if (item.action == Action::ACCEPT)
        {
            cout << "Nenhum erro sintático encontrado" << endl;
            return 0;
        }
        else
        {
            cout << item.action << " " << item.id << "[" << item.i << ", " << item.j << "]" << endl;
            puts("> Syntax error at token:");

            for (int window = -5; window <= 7; window++)
            {
                if (head + window >= 0 && head + window < (int)tokenList.size())
                {
                    if (window == 0)
                        printf(" >>>>");
                    else
                        printf(" ");
                    printf("%s", lexeme_to_str(inputTokens[head + window].lexeme).c_str());
                }
            }

            int expectedSize = 0;
            int expected[NUM_TERMINALS];

            for (int k = 0; k < NUM_TERMINALS; k++)
            {
                if (actionTable[s][k].action != Action::ERROR)
                {
                    expected[expectedSize++] = Lexeme::_from_index(k);
                }
            }

            if (expectedSize == 1)
            {
                printf("... [ Expected a %s token ]\n", lexeme_to_str(Lexeme::_from_index(expected[0])).c_str());
                currTerminal = expected[0];
                puts("> Ignoring error and continuing analysis.");
            }
            else if (expectedSize > 1)
            {
                printf("... [ Ambiguous statement. Expected one of the following tokens: ");
                for (int k = 0; k < expectedSize; k++)
                {
                    printf("%s", lexeme_to_str(Lexeme::_from_index(expected[k])).c_str());
                    if (k < expectedSize - 1)
                        printf(", ");
                }
                printf(" ]\n");
                return 1;
            }

            return 1;
        }
    }
}

void printBadToken(Token t)
{
    cerr << "              \u001b[31m~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\033[0m" << endl;
    cerr << "              \u001b[31mErro:\033[0m Token inválido" << endl;
}

#endif
