class AF:

    def __init__(self):
        self.states = set()
        self.alphabet = set()
        self.transitions = []
        self.start = None
        self.final_states = []
        self.graph = dict()
        self.graph: dict[str, list[str]]

    def get_from_file(self, file_path: str):
        with open(file_path, 'r') as f:
            states = f.readline().strip().split(' ')
            self.states = set(states[1::])

            alphabet = f.readline().strip().split(' ')
            self.alphabet = set(alphabet[1::])

            transitions = []
            line = "placeholder"
            while line != "sfarsit":
                line = f.readline()
                if line == "sfarsit":
                    break
                line = line.strip()
                transitions.append(line)

            transitions = self.__process_transitions(transitions[1:-1:])
            self.transitions = transitions

            start = f.readline().strip().split(' ')
            self.start = start[1]

            final_states = f.readline().strip().split(' ')
            self.final_states = set(final_states[1::])

    def __process_transitions(self, transitions):
        result = []

        for state in self.states:
            self.graph[state] = []

        for t in transitions:
            elements = t.split('~')
            result.append((elements[0], elements[2], set(elements[1])))
            if elements[0] not in self.states or elements[2] not in self.states:
                raise ValueError("Invalid state in transitions list!")
            self.graph[elements[0]].append((elements[2], elements[1]))

        return result

    def get_from_input(self):
        states = set(input("stari: ").strip().split(' '))
        alphabet = set(input('alfabet: ').strip().split(' '))
        self.states = states
        self.alphabet = alphabet
        transitions = []
        input_value = "placeholder"
        while input_value != "sfarsit":
            input_value = input('tranz: ').strip()
            transitions.append(input_value)

        transitions = self.__process_transitions(transitions[:-1:])
        start = input('start: ').strip().split(' ')[0]
        final_states = set(input('F: ').strip().split(' '))
        self.transitions = transitions
        self.start = start
        self.final_states = final_states

    def print_data(self):
        print(f"Stari: {self.states}")
        print(f"Alfabet: {self.alphabet}")
        print(f"Tranz: {self.transitions}")
        print(f"Start: {self.start}")
        print(f"F: {self.final_states}")

    def __evaluate(self, value, index):

        if not value:
            if index in self.final_states:
                return True
            return False

        evaluation_result = False
        neigh_list = self.graph.get(index)
        for neighbor in neigh_list:
            if value[0] in neighbor[1]:
                evaluation_result = evaluation_result or self.__evaluate(value[1::], neighbor[0])

        return evaluation_result

    def __update_result(self, prefix, solution):
        if len(solution) > len(prefix):
            prefix.clear()
            prefix.extend(solution.copy())

    def __get_longest_prefix(self, value, index, prefix, solution):
        if not value:
            self.__update_result(prefix, solution)

        neigh_list = self.graph.get(index)
        for neighbor in neigh_list:
            if value[0] in neighbor[1]:
                solution.append(value[0])
                self.__get_longest_prefix(value[1::], neighbor[0], prefix, solution)
                solution.pop()

        self.__update_result(prefix, solution)

    def get_longest_prefix(self, value):
        prefix = []
        index = self.start
        self.__get_longest_prefix(value, index, prefix, [])
        return "".join([x for x in prefix])

    def evaluate(self, value):
        index = self.start
        return self.__evaluate(value, index)
