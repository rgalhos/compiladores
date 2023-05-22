import pandas as pd
from csnake import CodeWriter, Enum
from parglare import Parser, Grammar


def table_entry(value):
    value = value.split(':')
    if value[0][1] == 'A':
        return "acc"
    return value[0][1].lower() + value[1].replace(']', '')


actionsEnum = {
    'SHIFT': 0,
    'REDUCE': 1,
    'ACCEPT': 2,
    'ERROR': 3
}

def get_action_table_entry(action_value):
    if action_value == '':
        return {'action': actionsEnum['ERROR'], 'id': 0}
    elif action_value == 'acc':
        return {'action': actionsEnum['ACCEPT'], 'id': 0}
    elif action_value[0] == 's':
        return {'action': actionsEnum['SHIFT'], 'id': action_value[1:]}
    elif action_value[0] == 'r':
        return {'action': actionsEnum['REDUCE'], 'id': action_value[1:]}


if __name__ == "__main__":
    with open('grammar.pg', 'r') as file:
        grammar = file.read()

    g = Grammar.from_string(grammar)

    prods = g.productions

    parser = Parser(g)
    table = parser.table

    num_states = len(table.states)
    non_terminals = " ".join(g.nonterminals.keys()).replace("S'", '')
    terminals = " ".join(g.terminals.keys())

    num_non_terminals = len(non_terminals.strip(' ').split(' '))
    num_terminals = len(terminals.split(' '))
    num_prods = len(prods) - 1
 
    print(f"Número de estados:\t {num_states}")
    print(f"Número de produções:\t {num_prods}")
    print(f"Número de símbolos terminais:\t {num_terminals}")
    print(f"Número de símbolos não terminais:\t {num_non_terminals}")

    df = pd.DataFrame(
        index=range(num_states), columns=(terminals + ' ' + non_terminals).split(" ")
    )

    for i, state in enumerate(table.states):
        for symbol, action in state.actions.items():
            df.at[i, str(symbol)] = table_entry(str(action))

        for symbol, go in state.gotos.items():
            df.at[i, str(symbol)] = str(go.state_id)

    df = df.fillna('')

    cw = CodeWriter()

    cw.add_line('#ifndef CONSTANTS_CPP')
    cw.add_define('CONSTANTS_CPP')
    
    cw.add_line('')

    # include stdio.h and stdlib.h
    cw.add_define('NUM_STATES', num_states)
    cw.add_define('NUM_PRODUCTIONS', num_prods)
    cw.add_define('NUM_TERMINALS', num_terminals)
    cw.add_define('NUM_NON_TERMINALS', num_non_terminals)

    cw.add_line('')

    cw.add_line('#endif')

    cw.add_line('')


    nt2int = {}

    for i, nonterminal in enumerate(non_terminals.strip(' ').split(' ')):
        nt2int[nonterminal] = i

    production_array = [
        (nt2int[str(p.symbol)], len(p.rhs)) for p in prods[1:]
    ]

    with open('productions.txt', 'w') as file:
        for p in production_array:
            file.write(f"{p[0]} {p[1]}\n")

    # Lista de ações
    action_table = df[terminals.split(' ')].to_numpy()

    with open('action_table.txt', 'w') as file:
        for i, row in enumerate(action_table):
            for j, entry in enumerate(row):
                action, id_ = get_action_table_entry(entry).values()
                file.write(f"{action} {id_}\n")

    # Tabela GOTO
    goto_table = df[non_terminals.strip(' ').split(' ')].replace('', 0).to_numpy()

    with open('goto_table.txt', 'w') as file:
        for i, row in enumerate(goto_table):
            for j, entry in enumerate(row):
                file.write(f"{entry}\n")

    cw.write_to_file('../src/syntactic/constants.cpp')
