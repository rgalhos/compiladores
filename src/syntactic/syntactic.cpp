#ifndef SYNTACTIC_CPP
#define SYNTACTIC_CPP

#define N_STATES 211
#define N_PRODUCTIONS 102
#define TERMINAL_SIZE 51
#define NON_TERMINAL_SIZE 47

#define DEBUG if (1)

#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include "../lexical/token.cpp"

using namespace std;

typedef struct
{
    int left;
    int rightSize;
} Production;

typedef enum
{
    SHIFT,
    REDUCE,
    ACCEPT,
    ERROR,
} Action;

typedef struct
{
    int id;
    Action action;
    int i;
    int j;
} TableEntry;

void readProductions();
void readActionTable();
void readGoToTable();
int parseTokens();
void printBadToken(Token t);

vector<Token> tokenList;
vector<Production> productions;
TableEntry actionTable[N_STATES][TERMINAL_SIZE];
int goTable[N_STATES][NON_TERMINAL_SIZE];

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

    readProductions();
    readActionTable();
    readGoToTable();

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

    int teste = 0;

    while (true)
    {
        teste++;
        int s = pilha.top();

        TableEntry entry = actionTable[s][currTerminal];

        if (entry.action == Action::SHIFT)
        {
            pilha.push(entry.id);
            currTerminal = lexeme_to_int(inputTokens[++head].lexeme);
        }
        else if (entry.action == Action::REDUCE)
        {
            for (int i = 0; i < productions[entry.id - 1].rightSize; i++)
                pilha.pop();

            s = pilha.top();
            pilha.push(goTable[s][productions[entry.id - 1].left]);
        }
        else if (entry.action == Action::ACCEPT)
        {
            cout << "AEEEEEEEEEEEEEHOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO" << endl;
            return 1;
        }
        else
        {
            cout << teste << endl;
            cout << entry.action << " " << entry.id << "[" << entry.i << ", " << entry.j << "]" << endl;
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
            int expected[TERMINAL_SIZE];

            for (int k = 0; k < TERMINAL_SIZE; k++)
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
                return 0;
            }
            return 0;
        }
    }
}

void printBadToken(Token t)
{
    cerr << "              \u001b[31m~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\033[0m" << endl;
    cerr << "              \u001b[31mErro:\033[0m Token inválido" << endl;
}

void readProductions()
{
    ifstream fin("bnf/productions.txt");
    int left, rightSize;

    while (fin.good())
    {
        fin >> left >> rightSize;

        if (fin.eof())
            break;

        productions.push_back(Production{
            .left = left,
            .rightSize = rightSize,
        });
    }

    fin.close();
}

void readActionTable()
{
    ifstream fin("bnf/action_table.txt");
    char line[32];

    for (int i = 0; i < N_STATES; i++)
    {
        for (int j = 0; j < TERMINAL_SIZE; j++)
        {
            fin.getline(line, 32);

            if (fin.eof())
                break;

            char *t = strtok(line, " ");
            actionTable[i][j].action = (Action)atoi(t);

            t = strtok(NULL, " ");
            actionTable[i][j].id = atoi(t);

            actionTable[i][j].i = i;
            actionTable[i][j].j = j;
        }
    }
}

void readGoToTable()
{
    ifstream fin("bnf/goto_table.txt");
    int state;

    for (int i = 0; i < N_STATES; i++)
    {
        for (int j = 0; j < NON_TERMINAL_SIZE; j++)
        {
            fin >> state;

            if (fin.eof())
                break;

            goTable[i][j] = state;
        }
    }
}

#endif
