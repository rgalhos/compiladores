#include <iostream>
#include <fstream>
#include <ctype.h>
#include <list>
#include "token.cpp"

#define MAX_LEXEME_LEN 1024

using namespace std;

int lex();
void lookup(char);
void getNonBlank();
void getChar();
void addChar();
void putToken(Lexeme l);
void putToken(Lexeme l, auto val);

bool issymbol(char);

void readIdentifier();
void readIntegerOrReal();

char nextChar = '\0';
Token nextToken(Lexeme::UNKNOWN, 0, 0);   // placeholder
CharClass charClass = CharClass::UNKNOWN; // placeholder

int line = 0, column = 1;
char currentTerm[MAX_LEXEME_LEN];
int currentTermLen = 0;

ifstream *fin;

int parse_file(char *fileName, list<Token> *tokenList)
{
    fin = new ifstream(fileName);

    if (fin->is_open())
    {
        getChar();

        do
        {
            lex();
            tokenList->push_back(nextToken);
        } while (fin->good() && (nextToken.lexeme != +Lexeme::DEL_DOT));
    }
    else
    {
        cerr << "Não foi possível abrir o arquivo" << endl;
        return 1;
    }

    fin->close();

    return 0;
}

void getNonBlank()
{
    while (isspace(nextChar) && !fin->fail())
        getChar();
}

void addChar()
{
    if (currentTermLen < MAX_LEXEME_LEN)
    {
        currentTerm[currentTermLen++] = nextChar;
        currentTerm[currentTermLen] = '\0';
    }
    else
    {
        cerr << "Erro: Lexema muito longo" << endl;
    }
}

void getChar()
{
    if (fin->get(nextChar) && !fin->eof())
    {
        if (isalpha(nextChar))
        {
            charClass = CharClass::LETTER;
        }
        else if (isdigit(nextChar))
        {
            charClass = CharClass::DIGIT;
        }
        else if (issymbol(nextChar))
        {
            charClass = CharClass::SYMBOL;
        }
        else
        {
            charClass = CharClass::UNKNOWN;
        }

        column++;
        if (nextChar == '\n')
        {
            column = 1;
            line++;
        }
    }
    else
    {
        charClass = CharClass::CHAR_EOF;
    }
}

void readIdentifier()
{
    addChar();
    getChar();

    while (charClass == +CharClass::LETTER || charClass == +CharClass::DIGIT)
    {
        addChar();
        getChar();
    }

    putToken(Lexeme::IDENTIFIER, currentTerm);
}

void readIntegerOrReal()
{
    bool isDouble = false;

    addChar();
    getChar();

    while (charClass == +CharClass::DIGIT)
    {
        addChar();
        getChar();
    }

    if (nextChar == '.')
    {
        isDouble = true;

        addChar();
        getChar();

        while (charClass == +CharClass::DIGIT)
        {
            addChar();
            getChar();
        }
    }

    if (isDouble)
    {
        putToken(Lexeme::CONST_REAL, strtod(currentTerm, NULL));
    }
    else
    {
        putToken(Lexeme::CONST_INTEGER, atoi(currentTerm));
    }
}

int lex()
{
    // Provavelmente é aqui que ocorre o bug de contar as colunas errado
    currentTermLen = 0;
    // Aqui ó -------^
    getNonBlank();

    switch (charClass)
    {
    case CharClass::LETTER:
        readIdentifier();
        break;

    case CharClass::DIGIT:
        readIntegerOrReal();
        break;

    case CharClass::CHAR_EOF:
        strcpy(currentTerm, "EOF\0");
        putToken(Lexeme::TK_EOF);
        break;

    default:
        lookup(nextChar);
        getChar();
        break;
    }

    return 0;
}

void lookup(char c)
{
    addChar();

    switch (c)
    {
    case '+':
        putToken(Lexeme::OP_SUM);
        break;

    case '-':
        putToken(Lexeme::OP_SUB);
        break;

    case '*':
        putToken(Lexeme::OP_MUL);
        break;

    case '/':
        if (fin->peek() == '/')
        {
            getChar();
            addChar();
            putToken(Lexeme::OP_DIV_INT);
        }
        else
        {
            putToken(Lexeme::OP_DIV);
        }
        break;

    case '=':
        putToken(Lexeme::RELOP_EQUAL);
        break;

    case '>':
        if (fin->peek() == '=')
        {
            getChar();
            addChar();
            putToken(Lexeme::RELOP_GREATER_OR_EQ_THAN);
        }
        else
        {
            putToken(Lexeme::RELOP_GREATER_THAN);
        }
        break;

    case '<':
        if (fin->peek() == '=')
        {
            getChar();
            addChar();
            putToken(Lexeme::RELOP_LESS_OR_EQ_THAN);
        }
        else if (fin->peek() == '>')
        {
            getChar();
            addChar();
            putToken(Lexeme::RELOP_NOT_EQUAL);
        }
        else
        {
            putToken(Lexeme::RELOP_LESS_THAN);
        }
        break;

    case ':':
        if (fin->peek() == '=')
        {
            getChar();
            addChar();
            putToken(Lexeme::VALUE_ASSIGN);
        }
        else
        {
            putToken(Lexeme::TYPE_ASSIGN);
        }
        break;

    case '(':
        putToken(Lexeme::DEL_OPEN_PAREN);
        break;

    case ')':
        putToken(Lexeme::DEL_CLOSE_PAREN);
        break;

    case '[':
        putToken(Lexeme::DEL_OPEN_BRACKETS);
        break;

    case ']':
        putToken(Lexeme::DEL_CLOSE_BRACKETS);
        break;

    case ';':
        putToken(Lexeme::DEL_SEMICOLON);
        break;

    case ',':
        putToken(Lexeme::DEL_COMMA);
        break;

    case '.':
        putToken(Lexeme::DEL_DOT);
        break;

    // Nunca chega:
    case EOF:
        putToken(Lexeme::TK_EOF);
        break;

    default:
        putToken(Lexeme::UNKNOWN);
        break;
    }
}

void putToken(Lexeme l)
{
    nextToken = Token(l, line, column - currentTermLen, currentTerm);
}

void putToken(Lexeme l, auto val)
{
    nextToken = Token(l, line, column - currentTermLen, val);
}

bool issymbol(char c)
{
    char list[] = "+-*/=><:()[];,.";

    for (size_t i = 0; i < strlen(list); i++)
        if (list[i] == c)
            return true;

    return false;
}
