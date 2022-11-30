#include <iostream>
#include <fstream>
#include <ctype.h>
#include "lexical/token.cpp"
#include "lexical/reserved_words.cpp"

#define MAX_LEXEME_LEN 1024

using namespace std;

int lex();
void getChar();
void getNonBlank();
void addChar();

void readIdentifier();
void readIntOrDoubleLit();

ifstream *fin;

bool readingString = false;
bool readingIntConst = false;
bool readingDoubleConst = false;
bool hasReadEscape = false;
Token nextToken(Lexeme::UNKNOWN, 0, 0); // placeholder
char nextChar;
Lexeme charClass = Lexeme::UNKNOWN; // placeholder

int line = 1;
int column = 1;

char term[MAX_LEXEME_LEN];
int termLen = 0;

int parse_file(char *fileName)
{
    fin = new ifstream(fileName);

    if (fin->is_open())
    {
        getChar();
        do
        {
            lex();
            cout << nextToken.to_string() << endl;
        } while (fin->good());
    }
    else
    {
        cerr << "Não foi possível abrir o arquivo" << endl;
        return 1;
    }

    fin->close();

    return 0;
}

void getChar()
{
    if (fin->get(nextChar) && !fin->eof())
    {
        if (isalpha(nextChar))
        {
            charClass = Lexeme::LETTER;
        }
        else if (isdigit(nextChar))
        {
            charClass = Lexeme::DIGIT;
        }
        else if (ispunct(nextChar))
        {
            charClass = Lexeme::SYMBOL;
        }
        else
        {
            charClass = Lexeme::UNKNOWN;
        }

        column++;
        if (nextChar == '\n')
        {
            line++;
            column = 0;
        }
    }
    else
    {
        // cout << "Chegou no fim do arquivo?" << endl;
        charClass = Lexeme::TK_EOF;
    }
}

void getNonBlank()
{
    while (isspace(nextChar) && !fin->fail())
    {
        getChar();
    }
}

Lexeme lookup(char c)
{
    switch (c)
    {
    case '!':
        addChar();
        nextToken = Token(Lexeme::LOGOP_NOT, line, column - termLen, term);
        break;

        // BINOP
    case '^':
        addChar();
        nextToken = Token(Lexeme::BINOP_POW, line, column - termLen, term);
        break;
    case '/':
        addChar();
        nextToken = Token(Lexeme::BINOP_DIV, line, column - termLen, term);
        break;
    case '*':
        addChar();
        nextToken = Token(Lexeme::BINOP_MUL, line, column - termLen, term);
        break;
    case '%':
        addChar();
        nextToken = Token(Lexeme::BINOP_MOD, line, column - termLen, term);
        break;
    case '+':
        addChar();
        nextToken = Token(Lexeme::BINOP_ADD, line, column - termLen, term);
        break;
    case '-':
        addChar();
        nextToken = Token(Lexeme::BINOP_SUB, line, column - termLen, term);
        break;

        // DEL
    case '(':
        addChar();
        nextToken = Token(Lexeme::DEL_OPEN_PAREN, line, column - termLen, term);
        break;
    case ')':
        addChar();
        nextToken = Token(Lexeme::DEL_CLOSE_PAREN, line, column - termLen, term);
        break;
    case '[':
        addChar();
        nextToken = Token(Lexeme::DEL_OPEN_BRACKETS, line, column - termLen, term);
        break;
    case ']':
        addChar();
        nextToken = Token(Lexeme::DEL_CLOSE_BRACKETS, line, column - termLen, term);
        break;
    case '{':
        addChar();
        nextToken = Token(Lexeme::DEL_OPEN_BRACES, line, column - termLen, term);
        break;
    case '}':
        addChar();
        nextToken = Token(Lexeme::DEL_CLOSE_BRACKETS, line, column - termLen, term);
        break;
    case ';':
        addChar();
        nextToken = Token(Lexeme::DEL_TERMINATOR, line, column - termLen, term);
        break;
    case '.':
        addChar();
        nextToken = Token(Lexeme::DEL_PERIOD, line, column - termLen, term);
        break;
    case ',':
        addChar();
        nextToken = Token(Lexeme::DEL_COMMA, line, column - termLen, term);
        break;
    case '\'':
        addChar();
        nextToken = Token(Lexeme::DEL_APOST, line, column - termLen, term);
        break;
    case '"':
        addChar();
        nextToken = Token(Lexeme::DEL_QUOT, line, column - termLen, term);
        break;

        // ASSIGN
    case '=':
        addChar();
        // TO DO: Verificar se o próximo é =
        nextToken = Token(Lexeme::ASSIGN_VALUE, line, column - termLen, term);
        break;

    case ':':
        addChar();
        nextToken = Token(Lexeme::ASSIGN_TYPE, line, column - termLen, term);
        break;

    // RELOP
    case '<':
        addChar();
        // TO DO: Verificar se o próximo é = (nesse caso é um RELOP_LESS_EQ)
        nextToken = Token(Lexeme::RELOP_LESS, line, column - termLen, term);
        break;

    case '>':
        addChar();
        // TO DO: Verificar se o próximo é = (nesse caso é um RELOP_GREATER_EQ)
        nextToken = Token(Lexeme::RELOP_GREATER, line, column - termLen, term);
        break;

    default:
        addChar();
        nextToken = Token(Lexeme::TK_EOF, line, column);
        break;
    }

    return nextToken.lexeme;
}

void addChar()
{
    if (termLen < MAX_LEXEME_LEN)
    {
        term[termLen++] = nextChar;
        term[termLen] = '\0';
    }
    else
    {
        cerr << "Erro: Lexema muito longo" << endl;
    }
}

int lex()
{
    termLen = 0;
    getNonBlank();

    switch (charClass)
    {
    case Lexeme::LETTER:
        readIdentifier();
        break;

    case Lexeme::DIGIT:
        readIntOrDoubleLit();
        break;

    case Lexeme::TK_EOF:
        strcpy(term, "EOF\0");
        nextToken = Token(Lexeme::TK_EOF, line, column - termLen, term);
        break;

    default:
        lookup(nextChar);
        getChar();
        break;
    }

    return 0;
}

void readIdentifier()
{
    do
    {
        addChar();
        getChar();
    } while (
        charClass == +Lexeme::LETTER                //
        || charClass == +Lexeme::DIGIT              //
        || (charClass == +Lexeme::SYMBOL            //
            && (nextChar == '_' || nextChar == '$') //
            ));

    nextToken = Token(Lexeme::IDENTIFIER, line, column - termLen, term);
}

void readIntOrDoubleLit()
{
    bool isDouble = false;
    addChar();
    getChar();

    while (charClass == +Lexeme::DIGIT)
    {
        addChar();
        getChar();
    }

    if (charClass == +Lexeme::DEL_PERIOD)
    {
        isDouble = true;
        while (charClass == +Lexeme::DIGIT)
        {
            addChar();
            getChar();
        }
    }

    if (isDouble)
    {
        nextToken = Token(Lexeme::CONST_DOUBLE, line, column - termLen, strtod(term, NULL));
    }
    else
    {
        nextToken = Token(Lexeme::CONST_INT, line, column - termLen, atoi(term));
    }
}
