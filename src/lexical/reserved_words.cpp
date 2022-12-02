#ifndef RESERVED_WORDS_CPP
#define RESERVED_WORDS_CPP

#include <string>
#include "lexeme.cpp"

Lexeme rw_checkIdentifier(std::string s)
{
    if (!s.compare("true"))
        return Lexeme::RW_TRUE;
    if (!s.compare("false"))
        return Lexeme::RW_FALSE;
    if (!s.compare("int"))
        return Lexeme::RW_INT;
    if (!s.compare("uint"))
        return Lexeme::RW_UINT;
    if (!s.compare("double"))
        return Lexeme::RW_DOUBLE;
    if (!s.compare("char"))
        return Lexeme::RW_CHAR;
    if (!s.compare("bool"))
        return Lexeme::RW_BOOL;
    if (!s.compare("string"))
        return Lexeme::RW_STRING;
    if (!s.compare("void"))
        return Lexeme::RW_VOID;
    if (!s.compare("var"))
        return Lexeme::RW_VAR;
    if (!s.compare("const"))
        return Lexeme::RW_CONST;
    if (!s.compare("function"))
        return Lexeme::RW_FUNCTION;
    if (!s.compare("if"))
        return Lexeme::RW_IF;
    if (!s.compare("else"))
        return Lexeme::RW_ELSE;
    if (!s.compare("for"))
        return Lexeme::RW_FOR;
    if (!s.compare("while"))
        return Lexeme::RW_WHILE;
    if (!s.compare("return"))
        return Lexeme::RW_RETURN;
    if (!s.compare("continue"))
        return Lexeme::RW_CONTINUE;
    if (!s.compare("break"))
        return Lexeme::RW_BREAK;
    if (!s.compare("readv"))
        return Lexeme::RW_READV;
    if (!s.compare("printv"))
        return Lexeme::RW_PRINTV;

    return Lexeme::IDENTIFIER;
}

#endif
