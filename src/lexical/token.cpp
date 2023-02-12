#include <string>
#include <stdint.h>
#include "reserved_words.cpp"
#include "lexeme.cpp"

enum ValueType
{
    INTEGER,
    REAL,
    LISTA,
    IDENTIFIER,
    NO_VAL
};

union numeric_val
{
    double _real;
    int _integer;
};

class Token
{
public:
    ValueType valueType;
    Lexeme lexeme = Lexeme::UNKNOWN;
    union numeric_val numericValue;
    char *content = NULL;
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

    void _init(Lexeme lexeme, int line, int column)
    {
        this->lexeme = lexeme;
        this->line = line;
        this->column = column;
        this->_checkIdentifier();
    }

public:
    Token(Lexeme lexeme, int line, int column)
    {
        this->valueType = ValueType::NO_VAL;
        _init(lexeme, line, column);
    }

    Token(Lexeme lexeme, int line, int column, int value)
    {
        this->valueType = ValueType::INTEGER;
        this->numericValue._integer = value;
        _init(lexeme, line, column);
    }

    Token(Lexeme lexeme, int line, int column, double value)
    {
        this->valueType = ValueType::REAL;
        this->numericValue._real = value;
        _init(lexeme, line, column);
    }

    Token(Lexeme lexeme, int line, int column, char *value)
    {
        this->valueType = ValueType::IDENTIFIER;
        int len = strlen(value) + 1;
        char *p = (char *)malloc(len * sizeof(char));
        strcpy(p, value);
        p[len] = '\0';
        this->content = p;
        _init(lexeme, line, column);
    }

    std::string value_to_str()
    {
        switch (this->valueType)
        {
        case ValueType::INTEGER:
            return std::to_string((this->numericValue)._integer);
        case ValueType::REAL:
            return std::to_string((this->numericValue)._real);
        case ValueType::IDENTIFIER:
            return std::string(this->content);
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
