#ifndef LEXEME_CPP
#define LEXEME_CPP

#include <enum.h>

BETTER_ENUM(CharClass, int,
            UNKNOWN = 1,

            LETTER,
            DIGIT,
            SYMBOL,
            ESCAPE,

            CHAR_EOF // EOF
);

BETTER_ENUM(Lexeme, int,
            UNKNOWN = 1,

            IDENTIFIER,
            CONST_INTEGER,
            CONST_REAL,
            CONST_LISTA,

            OP_SUM,     // +
            OP_SUB,     // -
            OP_MUL,     // *
            OP_DIV,     // /
            OP_DIV_INT, // //

            RELOP_EQUAL,              // =
            RELOP_LESS_THAN,          // >
            RELOP_GREATER_THAN,       // <
            RELOP_LESS_OR_EQ_THAN,    // >=
            RELOP_GREATER_OR_EQ_THAN, // <=
            RELOP_NOT_EQUAL,          // <>

            RW_PROGRAM,
            RW_PROCEDURE,
            RW_BEGIN,
            RW_END,
            RW_FUNCTION,
            RW_READ,
            RW_WRITE,
            RW_FOR,
            RW_TO,
            RW_DO,
            RW_REPEAT,
            RW_UNTIL,
            RW_WHILE,
            RW_IF,
            RW_ELSE,
            RW_THEN,
            RW_VAR,
            RW_INTEGER,
            RW_REAL,
            RW_CONCATENA,
            // opLista:
            RW_LENGTH,
            RW_HEAD,
            RW_TAIL,

            VALUE_ASSIGN, // :=
            TYPE_ASSIGN,  // :

            DEL_OPEN_PAREN,     // (
            DEL_CLOSE_PAREN,    // )
            DEL_OPEN_BRACKETS,  // [
            DEL_CLOSE_BRACKETS, // ]
            DEL_SEMICOLON,      // ;
            DEL_COMMA,          // ,
            DEL_DOT,            // •

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
