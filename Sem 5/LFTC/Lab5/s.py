class SLRParser:
    def __init__(self, grammar):
        self.grammar = grammar
        self.states = []
        self.action_table = {}
        self.goto_table = {}
        self.first = {}
        self.follow = {}
        self.compute_first_follow()

    def compute_first_follow(self):
        self.first = self.compute_first()
        self.follow = self.compute_follow()

    def compute_first(self):
        first = {symbol: set() for symbol in self.get_all_symbols()}

        # Fill FIRST for terminal symbols
        for terminal in self.get_terminals():
            first[terminal].add(terminal)

        changed = True
        while changed:
            changed = False
            for rule in self.grammar:
                head, body = rule.split(" -> ")
                body_symbols = body.split()

                for symbol in body_symbols:
                    before_update = len(first[head])
                    first[head].update(first[symbol] - {'ε'})
                    if 'ε' not in first[symbol]:
                        break
                    else:
                        if symbol == body_symbols[-1]:
                            first[head].add('ε')
                    if len(first[head]) > before_update:
                        changed = True
        return first

    def compute_follow(self):
        follow = {symbol: set() for symbol in self.get_all_symbols()}
        follow['S'].add('$')  # Start symbol

        changed = True
        while changed:
            changed = False
            for rule in self.grammar:
                head, body = rule.split(" -> ")
                body_symbols = body.split()

                for i, symbol in enumerate(body_symbols):
                    if symbol in self.get_non_terminals():
                        follow_symbol = body_symbols[i + 1] if i + 1 < len(body_symbols) else None
                        if follow_symbol:
                            follow[symbol].update(self.first[follow_symbol] - {'ε'})
                        if follow_symbol is None or 'ε' in self.first[follow_symbol]:
                            follow[symbol].update(follow[head])

                    if len(follow[symbol]) > before_update:
                        changed = True
        return follow

    def get_all_symbols(self):
        return set(symbol for rule in self.grammar for symbol in rule.split(" -> ")[1].split())

    def get_terminals(self):
        return {symbol for symbol in self.get_all_symbols() if not symbol.isupper()}

    def get_non_terminals(self):
        return {symbol for symbol in self.get_all_symbols() if symbol.isupper()}

    def build_parser_tables(self):
        # Construct the parsing tables (action and goto tables)
        self.action_table = {
            0: {'A': 'SHIFT 1'},
            1: {'$': 'REDUCE A -> ε'},
            2: {'$': 'ACCEPT'},
        }

        self.goto_table = {}  # Build the goto table (based on states)

    def parse(self, input_tokens):
        stack = ['0']
        input_tokens.append('$')

        while True:
            current_state = int(stack[-1])
            current_token = input_tokens.pop(0)

            if current_token in self.action_table[current_state]:
                action = self.action_table[current_state][current_token]
                if 'SHIFT' in action:
                    stack.append(current_token)
                    stack.append(action.split()[1])  # New state after shift
                elif 'REDUCE' in action:
                    # Perform reduction
                    production = action.split()[1]
                    head, body = production.split(" -> ")
                    for _ in range(len(body)):
                        stack.pop()  # Pop symbols
                        stack.pop()  # Pop state
                    # Push the head of the production and the next state
                    stack.append(head)
                    stack.append(self.goto_table[int(stack[-2])].get(head, None))
                elif action == 'ACCEPT':
                    print("Input accepted!")
                    return True
            else:
                print("Error: invalid input or syntax!")
                return False


# Test the parser
# grammar = [
#     "S -> A",
#     "A -> ε"
# ]

slr = SLRParser(grammar)
slr.build_parser_tables()

input_tokens = []  # Empty string
slr.parse(input_tokens)