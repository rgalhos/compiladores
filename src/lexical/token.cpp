#include <string>
#include <stdint.h>
#include "reserved_words.cpp"
#include "lexeme.cpp"

enum ValueType
{
    INT,
    UINT,
    CHAR,
    STRING,
    DOUBLE,
    NO_VAL
};

union numeric_val
{
    char _char;
    int _int;
    unsigned int _uint;
    double _double;
};

class Token
{
public:
    ValueType tokenType;
    Lexeme lexeme = Lexeme::UNKNOWN;
    void *value = NULL;
    union numeric_val num_val;
    int line;
    int column;

private:
    void _checkIdentifier()
    {
        if (this->lexeme == +Lexeme::IDENTIFIER)
        {
            this->lexeme = rw_checkIdentifier(this->value_to_str());
        }
    }

    void _init(Lexeme lexeme, int line, int column, void *value)
    {
        this->lexeme = lexeme;
        this->line = line;
        this->column = column;
        this->tokenType = tokenType;
        this->value = value;
        this->_checkIdentifier();
    }

public:
    Token(Lexeme lexeme, int line, int column)
    {
        this->tokenType = ValueType::NO_VAL;
        _init(lexeme, line, column, NULL);
    }

    Token(Lexeme lexeme, int line, int column, int value)
    {
        this->tokenType = ValueType::INT;
        this->num_val._int = value;
        _init(lexeme, line, column, NULL);
    }

    Token(Lexeme lexeme, int line, int column, unsigned int value)
    {
        this->tokenType = ValueType::UINT;
        this->num_val._uint = value;
        _init(lexeme, line, column, NULL);
    }

    Token(Lexeme lexeme, int line, int column, double value)
    {
        this->tokenType = ValueType::DOUBLE;
        this->num_val._double = value;
        _init(lexeme, line, column, NULL);
    }

    Token(Lexeme lexeme, int line, int column, char value)
    {
        this->tokenType = ValueType::CHAR;
        this->num_val._char = value;
        _init(lexeme, line, column, NULL);
    }

    Token(Lexeme lexeme, int line, int column, char *value)
    {
        this->tokenType = ValueType::STRING;
        int len = strlen(value) + 1;
        char *p = (char *)malloc(len * sizeof(char));
        strcpy(p, value);
        p[len] = '\0';
        _init(lexeme, line, column, (void *)&value);
    }

    ~Token()
    {
        if (this->tokenType == +ValueType::STRING)
        {
            // free() TO DO
        }
        else
        {
            free(this->value);
        }
    }

    std::string value_to_str()
    {
        switch (this->tokenType)
        {
        case ValueType::INT:
            return std::to_string((this->num_val)._int);
        case ValueType::UINT:
            return std::to_string((this->num_val)._uint);
        case ValueType::DOUBLE:
            return std::to_string((this->num_val)._double);
        case ValueType::CHAR:
            return std::string({(this->num_val)._char, '\0'});
        case ValueType::STRING:
            return std::string(*(char **)this->value);
        default:
            return "";
        }
    }

    std::string to_string()
    {
        char tmp[256];
        snprintf(tmp, 256, "              [%04d, %04d] (%04d, %20s) {%s}", this->line, this->column, lexeme_to_int(this->lexeme), lexeme_to_str(this->lexeme).c_str(), this->value_to_str().c_str());
        return std::string(tmp);
    }
};
