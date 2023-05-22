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

    cout << endl
         << endl;

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
            Token currToken = inputTokens[head];

            cout << "Erro sintático encontrado na linha " << currToken.line << ", coluna " << currToken.column << "!" << endl;
            //cout << currToken.to_string() << endl;

            int charCount = 0, errStart = 0, errSize = 0;
            for (int i = -4; i < 4; i++)
            {
                if (head + i < 0 || head + i > (int)inputTokens.size())
                    continue;

                string t = lexeme_to_str(inputTokens[head + i].lexeme);

                if (i == 0)
                {
                    cout << " \u001b[31m" << t << "\033[0m";
                    errStart = charCount;
                    errSize = t.size();
                }
                else
                {
                    cout << " " << t;
                }

                charCount += t.size() + 1;
            }

            cout << endl;
            for (int i = 0; i < charCount; i++)
            {
                if (i > errStart && i < errStart + errSize + 1)
                    cout << "\u001b[31m^\033[0m";
                else
                    cout << "~";
            }
            cout << endl;

            vector<int> expectedTokens;

            for (int i = 0; i < NUM_TERMINALS; i++)
            {
                if (actionTable[s][i].action != Action::ERROR)
                {
                    expectedTokens.push_back(i);
                }
            }

            if (expectedTokens.size() == 1)
            {
                cout << "Token esperado: \"" << lexeme_to_str(Lexeme::_from_index(expectedTokens[0])).c_str() << "\"" << endl;
                return 0;
            }
            else
            {
                cout << "Um dos seguintes tokens era esperado: ";
                for (int t : expectedTokens)
                {
                    cout << lexeme_to_str(Lexeme::_from_index(t)).c_str() << " ";
                }
                cout << endl;

                return 0;
            }
        }
    }
}

void printBadToken(Token t)
{
    cerr << "              \u001b[31m~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\033[0m" << endl;
    cerr << "              \u001b[31mErro:\033[0m Token inválido" << endl;
}

#endif
