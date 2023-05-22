program meuPrograma;

var teste: integer;

function maior(a: integer, b: integer): integer; begin
    if (>=(a, b)) then begin
        write(a);
    end else begin
        write(b);
    end
end

begin
    
end

.

programa
    corpo
        declara
            dvar
                mais_var
                tipo_var
                primitivos
            mais_dc
                +DEL_SEMICOLON
                cont_dc
        rotina
            funcao
                +RW_FUNCTION
                +IDENTIFIER (maior)
                parametros
                    +DEL_OPEN_PAREN
                    lista_parametros
                        lista_id
                            +IDENTIFIER (a)
                            cont_lista_id
                            +TYPE_ASSIGN
                            tipo_var
                                primitivos
                                    +RW_INTEGER
                            cont_lista_par
                                +DEL_COMMA
                                lista_parametros
                                    lista_id
                                        +IDENTIFIER (b)
                                        cont_lista_id
                                +TYPE_ASSIGN
                                tipo_var
                                    primitivos
                                        +RW_INTEGER
                    +DEL_CLOSE_PAREN
                +TYPE_ASSIGN
                tipo_funcao
                    primitivos
                        +RW_INTEGER
                +DEL_SEMICOLON
                corpo
                    declara
                    rotina
                    +RW_BEGIN
                    corpo_sentencas
                        sentencas
                            comando
                                +RW_IF
                                +DEL_OPEN_PAREN
                                condicao
                                    relop
                                        +RELOP_GREATER_OR_EQ_THAN
                                    +DEL_OPEN_PAREN
                                    expressao_num
                                        termo
                                            +IDENTIFIER (a)
                                    +DEL_COMMA
                                    expressao_num
                                        termo
                                            +IDENTIFIER (b)
                                    +DEL_CLOSE_PAREN
                                +RW_THEN
                                +RW_BEGIN
                                sentencas
                                    comando
                                        +RW_WRITE
                                        +DEL_OPEN_PAREN
                                        var_write
                                            IDENTIFIER (a)
                                            mais_var_write
                                        +DEL_CLOSE_PAREN
                                    mais_sentencas
                                        +DEL_SEMICOLON
                                        cont_sentencas
                                +RW_END
                                pfalsa
                                    +RW_ELSE
                                    +RW_BEGIN
                                    sentencas
                                        comando
                                            +RW_WRITE
                                            +DEL_OPEN_PAREN
                                            var_write
                                                IDENTIFIER (a)
                                                mais_var_write
                                            +DEL_CLOSE_PAREN
                                        mais_sentencas
                                            +DEL_SEMICOLON
                                            cont_sentencas
                                    +RW_END
                            mais_sentencas
                    +RW_END
        +RW_BEGIN
        corpo_sentencas
        +RW_END
    final
    +DEL_DOT
