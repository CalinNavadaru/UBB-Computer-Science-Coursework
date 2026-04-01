class SLR:
    def __init__(self, list_prod: list[str]):
        self.first = None
        self.follow = None
        self.slr_table = None
        self.list_prod = list_prod
        self.states = []
        self.starting_symbol = list_prod[0][0]


    def augment_grammar(self):
        self.list_prod.insert(0, f"D -> {self.starting_symbol}")
        self.starting_symbol = "D"

    def add_dots(self):
        for i in range(len(self.list_prod)):
            l = self.list_prod[i].split(" ")
            l.insert(2, ".")
            self.list_prod[i] = " ".join(l)

    def closure(self, state):
        new_state = state[:]
        added = True
        while added:
            added = False
            for production in new_state:
                if '.' in production:
                    parts = production.split(" ")
                    index_point = parts.index('.')
                    if index_point < len(parts) - 1:
                        next_symbol = parts[index_point + 1]
                        if next_symbol.isupper():
                            for prod in self.list_prod:
                                if prod.startswith(next_symbol) and prod not in new_state:
                                    new_state.append(prod)
                                    added = True
        return new_state

    def goto(self, state, symbol):
        new_state = list()
        for production in state:
            if '.' in production:
                parts = production.split(" ")
                idx = parts.index('.')
                if idx + 1 < len(parts) and parts[idx + 1] == symbol:
                    new_prod = " ".join(parts[:idx] + [parts[idx + 1]] + ["."] + parts[idx + 2:])
                    new_state.append(new_prod)
        return self.closure(new_state)

    def build_states(self):
        initial_state = self.closure([self.list_prod[0]])
        self.states.append(initial_state)
        while True:
            new_states = []
            for state in self.states:
                for symbol in self.get_next_symbols(state):
                    new_state = self.goto(state, symbol)
                    if new_state not in self.states:
                        self.states.append(new_state)
                        new_states.append(new_state)
            if not new_states:
                break

    def get_next_symbols(self, state):
        symbols = set()
        for production in state:
            parts = production.split(" ")
            if '.' in parts:
                idx = parts.index('.')
                if idx + 1 < len(parts):
                    symbols.add(parts[idx + 1])
        return symbols

    def get_all_symbols(self):
        result = set()
        for prod in self.list_prod:
            p = prod.split(" ")
            result.add(p[0])
            for i in range(2, len(p)):
                result.add(p[i])

        return result

    def get_terminals(self):
        result = set()
        for prod in self.list_prod:
            p = prod.split(" ")
            for i in range(2, len(p)):
                if p[i].islower():
                    result.add(p[i])

        return result

    def get_nonterminals(self):
        result = set()
        for prod in self.list_prod:
            p = prod.split(" ")
            result.add(p[0])

        return result

    def compute_first(self):
        self.first = {symbol: set() for symbol in self.get_all_symbols()}
        for terminal in self.get_terminals():
            self.first[terminal].add(terminal)

        changed = True
        while changed:
            changed = False
            for prod in self.list_prod:
                head, body = prod.split(" -> ")
                body_symbols = body.split(" ")

                for symbol in body_symbols:
                    before_update = len(self.first[head])
                    self.first[head].update(self.first[symbol] - {'ε'})
                    if len(self.first[head]) > before_update:
                        changed = True
                    if 'ε' not in self.first[symbol]:
                        continue
                    else:
                        if symbol == body_symbols[-1]:
                            self.first[head].add('ε')

                    if len(self.first[head]) > before_update:
                        changed = True

    def compute_follow(self):
        self.follow = {symbol: set() for symbol in self.get_nonterminals()}
        self.follow[self.starting_symbol].add('$')

        changed = True
        while changed:
            changed = False
            for prod in self.list_prod:
                head, body = prod.split(" -> ")
                body_symbols = body.split(" ")

                for i, symbol in enumerate(body_symbols):
                    if symbol in self.get_nonterminals():
                        before_update = len(self.follow[symbol])

                        for next_symbol in body_symbols[i + 1:]:
                            self.follow[symbol].update(self.first[next_symbol] - {'ε'})
                            if 'ε' not in self.first[next_symbol]:
                                break
                        else:
                            self.follow[symbol].update(self.follow[head])

                        if len(self.follow[symbol]) > before_update:
                            changed = True

    def build_slr_table(self):
        self.slr_table = {}
        for i, state in enumerate(self.states):
            self.slr_table[i] = {}

            for production in state:
                parts = production.split(" ")
                if '.' in parts:
                    idx = parts.index('.')

                    if idx == len(parts) - 1:
                        head = parts[0]
                        body = " ".join(parts[2:-1])
                        if head == "D":
                            self.slr_table[i]['$'] = "ACCEPT"
                        else:
                            for symbol in self.follow[head]:
                                self.slr_table[i][symbol] = f"REDUCE {head} -> {body}"
                    else:
                        next_symbol = parts[idx + 1]
                        new_state = self.goto(state, next_symbol)
                        if new_state in self.states:
                            next_state_idx = self.states.index(new_state)
                            if next_symbol.isupper():
                                self.slr_table[i][next_symbol] = next_state_idx
                            else:
                                self.slr_table[i][next_symbol] = f"SHIFT {next_state_idx}"

    def parse_input(self, input_string_arg):
        input_tokens = input_string_arg.split() + ['$']
        stack = [0]
        pointer = 0

        while True:
            state = stack[-1]
            current_token = input_tokens[pointer]
            action = self.slr_table[state].get(current_token)

            if action is None:
                raise ValueError(f"Eroare de sintaxă la simbolul: {current_token}")

            if action == "ACCEPT":
                print("Input acceptat!")
                break
            elif action.startswith("SHIFT"):
                _, next_state = action.split()
                stack.append(int(next_state))
                pointer += 1
            elif action.startswith("REDUCE"):
                _, production = action.split(" ", 1)
                head, body = production.split(" -> ")
                body_symbols = body.split()

                for _ in body_symbols:
                    stack.pop()
                goto_state = self.slr_table[stack[-1]].get(head)
                if goto_state is not None:
                    stack.append(goto_state)
                else:
                    raise ValueError(f"Eroare de sintaxă la simbolul: {current_token}")


grammar = [
    "S -> A x",
    "S -> B y",
    "A -> a",
    "B -> a"
]

slr = SLR(grammar)
slr.augment_grammar()
slr.compute_first()
slr.compute_follow()
slr.add_dots()
slr.build_states()
slr.build_slr_table()

for state_arg in slr.states:
    print(state_arg)

print("FIRST:", slr.first)
print("FOLLOW:", slr.follow)
print("SLR Table:", slr.slr_table)

input_string = "a t"
slr.parse_input(input_string)
