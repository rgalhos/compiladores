#include <iostream>
#include <locale.h>
#include <unistd.h>
#include "lexical/tokenizer.cpp"

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "Portuguese");

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

    return parse_file(argv[1]);
}
