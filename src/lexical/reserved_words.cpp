#ifndef RESERVED_WORDS_CPP
#define RESERVED_WORDS_CPP

#include <string>
#include "lexeme.cpp"

Lexeme rw_checkIdentifier(std::string s)
{
    if (!s.compare("program"))
        return Lexeme::RW_PROGRAM;
    if (!s.compare("procedure"))
        return Lexeme::RW_PROCEDURE;
    if (!s.compare("begin"))
        return Lexeme::RW_BEGIN;
    if (!s.compare("end"))
        return Lexeme::RW_END;
    if (!s.compare("function"))
        return Lexeme::RW_FUNCTION;
    if (!s.compare("read"))
        return Lexeme::RW_READ;
    if (!s.compare("write"))
        return Lexeme::RW_WRITE;
    if (!s.compare("for"))
        return Lexeme::RW_FOR;
    if (!s.compare("to"))
        return Lexeme::RW_TO;
    if (!s.compare("do"))
        return Lexeme::RW_DO;
    if (!s.compare("repeat"))
        return Lexeme::RW_REPEAT;
    if (!s.compare("until"))
        return Lexeme::RW_UNTIL;
    if (!s.compare("while"))
        return Lexeme::RW_WHILE;
    if (!s.compare("if"))
        return Lexeme::RW_IF;
    if (!s.compare("else"))
        return Lexeme::RW_ELSE;
    if (!s.compare("then"))
        return Lexeme::RW_THEN;
    if (!s.compare("var"))
        return Lexeme::RW_VAR;
    if (!s.compare("integer"))
        return Lexeme::RW_INTEGER;
    if (!s.compare("real"))
        return Lexeme::RW_REAL;
    if (!s.compare("concatena"))
        return Lexeme::RW_CONCATENA;
    if (!s.compare("length"))
        return Lexeme::RW_LENGTH;
    if (!s.compare("head"))
        return Lexeme::RW_HEAD;
    if (!s.compare("tail"))
        return Lexeme::RW_TAIL;

    return Lexeme::IDENTIFIER;
}

#endif