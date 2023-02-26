program testeLista;

var lista: [integer];

begin

    lista := concatena([], [1, 2, 3, 4, 5]);

    var tamanho: integer;
    tamanho := length(lista)

end

.

Dúvida 1: Não tem mesmo como declarar listas sem o `concatena([ ... ], [ ... ])` ?

Dúvida 2: Não se pode passar uma lista como argumento pelo nome da variável para length, concatena, head e tail?

<termo> ::= <operador> ( <operando> , <operando> ) | <id> | <integer_num> | <real_num>
<expressao_lista> ::= <oplista>(<conteudo>) | concatena(<conteudo> , <coneudo>)
<conteudo> ::= [] | [<integer_num><integer_num_cont>] | [<real_num><real_num_cont>]
<opLista> ::= length | head | tail

