#ifndef LEXEME_CPP
#define LEXEME_CPP

#include <enum.h>

BETTER_ENUM(Lexeme, int,
            UNKNOWN = 1,

            LETTER, // a-z A-Z
            DIGIT,  // 0-9
            SYMBOL, // ( ) [ ] { } + - / \ : ; ~ = ! ? < > . , & # @ | _ $ ' "
            ESCAPE, // \n \\ ' "

            IDENTIFIER,
            CONST_INT,
            CONST_UINT,
            CONST_CHAR,
            CONST_STRING,
            CONST_DOUBLE,

            RW_TRUE,
            RW_FALSE,
            RW_INT,
            RW_UINT,
            RW_DOUBLE,
            RW_CHAR,
            RW_BOOL,
            RW_STRING,
            RW_VOID,
            RW_VAR,
            RW_CONST,
            RW_FUNCTION,
            RW_IF,
            RW_ELSE,
            RW_FOR,
            RW_WHILE,
            RW_RETURN,
            RW_CONTINUE,
            RW_BREAK,
            RW_READV,
            RW_PRINTV,

            BINOP_POW, // ^
            BINOP_DIV, // /
            BINOP_MUL, // *
            BINOP_MOD, // %
            BINOP_ADD, // +
            BINOP_SUB, // -

            ASSIGN_VALUE, // =
            ASSIGN_TYPE,  // :

            RELOP_LESS,       // <
            RELOP_LESS_EQ,    // <=
            RELOP_GREATER,    // >
            RELOP_GREATER_EQ, // >=
            RELOP_EQ,         // ==
            RELOP_NEQ,        // !=

            LOGOP_AND, // &&
            LOGOP_OR,  // ||
            LOGOP_NOT, // !

            DEL_OPEN_PAREN,     // (
            DEL_CLOSE_PAREN,    // )
            DEL_OPEN_BRACKETS,  // [
            DEL_CLOSE_BRACKETS, // ]
            DEL_OPEN_BRACES,    // {
            DEL_CLOSE_BRACES,   // }
            DEL_TERMINATOR,     // ;
            DEL_PERIOD,         // .
            DEL_COMMA,          // ,
            DEL_APOST,          // '
            DEL_QUOT,           // "

            TK_EOF // EOF
);

int lexeme_to_int(Lexeme l)
{
    return (+l);
}

std::string lexeme_to_str(Lexeme l)
{
    return l._to_string();
}

#endif