#include <iostream>
#include <locale.h>
#include <unistd.h>
#include <list>
#include "lexical/tokenizer.cpp"
#include "syntactic/syntactic.cpp"

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "Portuguese");

    /*
    for (int i = 0; i < 51; i++)
    {
        cout << i << " " << lexeme_to_str(Lexeme::_from_index(i)).c_str() << endl;
    }

    return 0;
    */

    if (argc == 1)
    {
        std::cout << "Utilização: " << argv[0] << " [file]" << std::endl;
        return 1;
    }

    if (access(argv[1], F_OK) != 0)
    {
        std::cout << "O arquivo \"" << argv[1] << "\" não existe ou não pode ser lido" << std::endl;
        return 2;
    }

    vector<Token> tokenList;

    parse_file(argv[1], &tokenList);
    syntatic_analyser(tokenList);

    return 0;
}
