import os.path
import sys
import af

if len(sys.argv) < 2:
    print("You must provide a MLP filepath! Exiting with error -1", file=sys.stderr, flush=True)
    sys.exit(-1)

filepath = sys.argv[1]

if not os.path.isfile(filepath):
    print("The provided path is invalid! Exiting with error -2", file=sys.stderr, flush=True)
    sys.exit(-2)


class FIPElement:
    def __init__(self, code, pos_ts_c, pos_ts_i):
        self.code = code
        self.pos_ts_c = pos_ts_c
        self.pos_ts_i = pos_ts_i

    def __str__(self):
        return f"Code: {self.code}; TSC: {self.pos_ts_c}; TSI: {self.pos_ts_i}"

    def __repr__(self):
        return f"Code: {self.code}; TSC: {self.pos_ts_c}; TSI: {self.pos_ts_i}"


class TS:
    def __init__(self):
        self.data = []

    def __str__(self):
        return str(self.data)

    def exists(self, atom):
        start = 0
        end = len(self.data) - 1
        while start <= end:
            middle = (start + end) // 2
            if self.data[middle] == atom:
                return middle
            elif self.data[middle] < atom:
                start = middle + 1
            else:
                end = middle - 1

        return None

    def add(self, atom):
        if self.exists(atom) is not None:
            return
        if len(self.data) == 0:
            self.data.append(atom)
        else:
            if str(atom) < str(self.data[0]):
                self.data.insert(0, atom)
            elif str(atom) > str(self.data[-1]):
                self.data.insert(len(self.data), atom)
            else:
                for index, element in enumerate(self.data[1:]):
                    if str(element) >= str(atom):
                        self.data.insert(index, atom)
                        return


KEYWORDS_SET = {"cin", "cout", "struct", "for", "while", "if", "int", "float", "str", "struct"}
OPERATORS_SET = {"+", "-", "*", "/", "**", "%", "//", "&&", "||", "<", ">", "<=", ">=", "==", "!=", "<<", ">>", "="}
SEPARATORS_SET = {"{", "}", ";", ",", "(", ")", "'"}

union_set = KEYWORDS_SET | OPERATORS_SET | SEPARATORS_SET

All_ATOMS = ["ID", "CONST", "cin", "while", "for", "cout", "struct", "if", "float", "int", "str", "+", "/", "!=", ">=",
             "<", ">", "-", "*", "&&", "||", "%", "//", "**", "<<", ">>", "=", "==", "<=", "{", "}", ";", ",", "(", ")",
             " ", "'"]

identifiers = set()
constants = set()
keywords = set()
operators = set()
separators = set()

af_identifiers = af.AF()
af_integers = af.AF()
af_floats = af.AF()
af_operators = af.AF()
af_separators = af.AF()
af_keywords = af.AF()
af_identifiers.get_from_file("automate/af_identificatori.txt")
af_integers.get_from_file("automate/af_const_intregi.txt")
af_floats.get_from_file("automate/af_const_reale.txt")
af_operators.get_from_file("automate/af_operatori.txt")
af_separators.get_from_file("automate/af_separatori.txt")
af_keywords.get_from_file("automate/af_keywords.txt")

fip: list[FIPElement] = []
ts_constants = TS()
ts_identifiers = TS()
queue_constants = []
queue_identifiers = []


def is_separator(element: str) -> bool:
    return element in SEPARATORS_SET


def is_operator(element: str) -> bool:
    return element in OPERATORS_SET


def is_keyword(element: str):
    return element in KEYWORDS_SET


def create_string_of_element(element: list[str]) -> str:
    element = "".join(char for char in element)
    element.strip()
    return element


def save_to_file():
    with open("output/tsc.txt", "w") as f:
        for element in ts_constants.data:
            f.write(f"{element}\n")

    with open("output/tsi.txt", "w") as f:
        for element in ts_identifiers.data:
            f.write(f"{element}\n")

    with open("output/fip.txt", "w") as f:
        for element in fip:
            f.write(
                f"Code: {element.code}; TSC: {element.pos_ts_c + 1 if element.pos_ts_c is not None else element.pos_ts_c};"
                f" TSI: {element.pos_ts_i + 1 if element.pos_ts_i is not None else element.pos_ts_i}\n")


def add_separator(element: str):
    separators.add(element)
    fip.append(FIPElement(All_ATOMS.index(element), None, None))


def add_operator(element: str):
    operators.add(element)
    fip.append(FIPElement(All_ATOMS.index(element), None, None))


def add_keyword(element: str):
    keywords.add(element)
    fip.append(FIPElement(All_ATOMS.index(element), None, None))


def add_constant(element: str):
    constants.add(element)
    ts_constants.add(element)
    fip.append(FIPElement(1, None, None))
    queue_constants.append(element)


def add_identifier(element: str):
    identifiers.add(element)
    ts_identifiers.add(element)
    queue_identifiers.append(element)
    fip.append(FIPElement(0, None, None))


def af_evaluate(element: list[str]):
    result_identifiers = af_identifiers.get_longest_prefix(element)
    result_integers = af_integers.get_longest_prefix(element)
    result_floats = af_floats.get_longest_prefix(element)
    result_operators = af_operators.get_longest_prefix(element)
    result_separators = af_separators.get_longest_prefix(element)
    result_keywords = af_keywords.get_longest_prefix(element)

    longest_prefix = ""
    evaluated = False
    token_type = ""
    element_str = "".join(element)

    if len(result_identifiers) > len(longest_prefix):
        index_identifier = element_str.find(result_identifiers)
        if result_identifiers not in KEYWORDS_SET and (
                is_separator(element[index_identifier + len(result_identifiers)]) or is_operator(
            element[index_identifier + len(result_identifiers)]) or element[
                    index_identifier + len(result_identifiers)].isspace()):
            longest_prefix = result_identifiers
            evaluated = True
            token_type = "IDENTIFICATOR"

    if len(result_keywords) > len(longest_prefix):

        index_keyword = element_str.find(result_keywords)
        if is_separator(element[index_keyword + len(result_keywords)]) or is_operator(element[index_keyword + len(result_keywords)]) or \
                element[index_keyword + len(result_keywords)].isspace():
            longest_prefix = result_keywords
            evaluated = True
            token_type = "CUVANT_CHEIE"

    if len(result_integers) > len(longest_prefix):

        index_integer = element_str.find(result_integers)
        if is_separator(element[index_integer + len(result_integers)]) or is_operator(element[index_integer + len(result_integers)]) or \
                element[index_integer + len(result_integers)].isspace():
            longest_prefix = result_integers
            evaluated = True
            token_type = "INTREG"

    if len(result_floats) > len(longest_prefix):
        index_float = element_str.find(result_floats)
        if is_separator(element[index_float + len(result_floats)]) or is_operator(element[index_float + len(result_floats)]) or element[
            index_float + len(result_floats)].isspace():
            longest_prefix = result_floats
            evaluated = True
            token_type = "REAL"

    if len(result_operators) > len(longest_prefix):
        longest_prefix = result_operators
        evaluated = True
        token_type = "OPERATOR"

    if len(result_separators) > len(longest_prefix):
        longest_prefix = result_separators
        evaluated = True
        token_type = "SEPARATOR"

    if evaluated:
        return token_type, longest_prefix

    return "EROARE", longest_prefix


def determine_type(token_type: str, atom: str):
    if token_type == "SEPARATOR":
        add_separator(atom)
    elif token_type == "OPERATOR":
        add_operator(atom)
    elif token_type in ["REAL", "INTREG"]:
        add_constant(atom)
    elif token_type == "CUVANT_CHEIE":
        add_keyword(atom)
    else:
        add_identifier(atom)


def main():
    with open(filepath, "r") as f:
        line_number = 1
        while line := f.readline():
            line = list(x for x in line) + [' ']
            index = 0
            while index < len(line):
                if line[index].isspace():
                    index += 1
                else:
                    token_type, prefix = af_evaluate(line[index:])
                    if token_type == "EROARE":
                        print(f"Eroare la {"".join(line[index:]).strip()} pe linia {line_number} la al {index + 1}-lea caracter")
                        while index < len(line) and not (is_separator(line[index]) or is_operator(line[index]) or line[index].isspace()):
                            index += 1
                    else:
                        determine_type(token_type, prefix)
                        index += len(prefix)

            line_number += 1

    for element in fip:
        if element.code == 1:
            element.pos_ts_c = ts_constants.exists(str(queue_constants[0]))
            queue_constants.pop(0)
        elif element.code == 0:
            element.pos_ts_i = ts_identifiers.exists(queue_identifiers[0])
            queue_identifiers.pop(0)

    print(f"Identificatori: {set(sorted(identifiers))}", end='\n')
    print(f"Separatori: {set(sorted(separators))}", end='\n')
    print(f"Cuvinte-cheie: {set(sorted(keywords))}", end='\n')
    print(f"Operatori: {set(sorted(operators))}", end='\n')
    print(f"Constante: {set(sorted(constants))}", end='\n')

    for index, el in enumerate(All_ATOMS):
        print(f"{index}, {el}", end='\n')
    print(f"FIP: {fip}", end='\n')
    print(f"TS constante: {ts_constants}", end='\n')
    print(f"TS identificatori: {ts_identifiers}", end='\n')

    save_to_file()


main()
