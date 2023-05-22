#ifndef PARSE_TABLES_CPP
#define PARSE_TABLES_CPP

#include <iostream>
#include <vector>
#include "./constants.cpp"

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
    int i, j;
} ActionTableItem;

void readProductions(vector<Production> *productions)
{
    ifstream fin("bnf/productions.txt");
    int left, rightSize;

    while (fin.good())
    {
        fin >> left >> rightSize;

        if (fin.eof())
            break;

        productions->push_back(Production{
            .left = left,
            .rightSize = rightSize,
        });
    }

    fin.close();
}

void readActionTable(ActionTableItem actionTable[NUM_STATES][NUM_TERMINALS])
{
    ifstream fin("bnf/action_table.txt");
    char line[32];

    for (int i = 0; i < NUM_STATES; i++)
    {
        for (int j = 0; j < NUM_TERMINALS; j++)
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

void readGotoTable(int gotoTable[NUM_STATES][NUM_NON_TERMINALS])
{
    ifstream fin("bnf/goto_table.txt");
    int state;

    for (int i = 0; i < NUM_STATES; i++)
    {
        for (int j = 0; j < NUM_NON_TERMINALS; j++)
        {
            fin >> state;

            if (fin.eof())
                break;

            gotoTable[i][j] = state;
        }
    }
}

#endif
