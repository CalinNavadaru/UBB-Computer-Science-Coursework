import os.path
import re
import sys

if len(sys.argv) < 2:
    print("You must provide a MLP filepath! Exiting with error -1", file=sys.stderr, flush=True)
    sys.exit(-1)

filepath = sys.argv[1]

if not os.path.isfile(filepath):
    print("The provided path is invalid! Exiting with error -2", file=sys.stderr, flush=True)
    sys.exit(-2)

KEYWORDS_SET = {"cin", "cout", "for", "while", "if", "int", "float", "str", "struct"}
OPERATORS_SET = {"+", "-", "*", "/", "**", "%", "//", "&&", "||", "<", ">", "<=", ">=", "==", "!=", "<<", ">>", "="}
SEPARATORS_SET = {"{", "}", ";", ",", "'", "(", ")", " "}

union_set = KEYWORDS_SET | OPERATORS_SET | SEPARATORS_SET

All_ATOMS = [
    "ID", "CONST", "cin", "while", "for", "cout", "struct", "if", "float", "int", "str",
    "+", "/", "!=", ">=", "<", ">", "-", "*", "&&", "||", "%", "//", "**", "<<", ">>",
    "=", "==", "<=", "{", "}", ";", ",", "'", "(", ")", " "
]


identifiers = set()
constants = set()
keywords = set()
operators = set()
separators = set()


class FIPElement:
    def __init__(self, code, pos_ts_c, pos_ts_i):
        self.code = code
        self.pos_ts_c = pos_ts_c
        self.pos_ts_i = pos_ts_i

    def __str__(self):
        return f"Code: {self.code}; TSC: {self.pos_ts_c}; TSI: {self.pos_ts_i}"

    def __repr__(self):
        return f"Code: {self.code}; TSC: {self.pos_ts_c}; TSI: {self.pos_ts_i}"

fip: list[FIPElement] = []

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


ts_constants = TS()
ts_identifiers = TS()
queue_constants = []
queue_identifiers = []


def is_string_constant(element: str):
    pattern = re.compile(r"^'.*'$")
    return re.match(pattern, element) is not None


def is_decimal_number(element: str):
    return element.isdigit()


def is_octal_number(element: str):
    pattern = re.compile(r"^O[0-7]+$")
    return re.match(pattern, element) is not None


def is_hexa_number(element: str):
    pattern = re.compile(r"^OX[0-9ABCDEF]+$")
    return re.match(pattern, element) is not None


def is_binary_number(element):
    pattern = re.compile(r"^b[0-1]+$")
    return re.match(pattern, element) is not None


def is_float_number(element):
    pattern = re.compile(r"^[0-9]+\.[0-9]*$|^[0-9]*\.[0-9]+$")
    return re.match(pattern, element)


def is_number(element: str):
    return len(element) > 0 and (is_decimal_number(element) or is_hexa_number(element) or is_octal_number(element)
                                 or is_binary_number(element) or is_float_number(element))


def is_identifier(element):
    pattern = re.compile(r"^[a-zA-Z_]+$")
    return pattern.match(element) is not None


def is_constant(element):
    return is_number(element) or is_string_constant(element)


def determine_type_element(element: str, line_number: int) -> None:

    if element in SEPARATORS_SET | KEYWORDS_SET | OPERATORS_SET:
        if element in SEPARATORS_SET:
            separators.add(element)
        elif element in KEYWORDS_SET:
            keywords.add(element)
        elif element in OPERATORS_SET:
            operators.add(element)
        if element != ' ':
            fip.append(FIPElement(All_ATOMS.index(element), None, None))
    elif is_constant(element):
        constants.add(element)
        ts_constants.add(element)
        fip.append(FIPElement(1, None, None))
        queue_constants.append(element)
    elif is_identifier(element):
        identifiers.add(element)
        ts_identifiers.add(element)
        queue_identifiers.append(element)
        fip.append(FIPElement(0, None, None))
    else:
        print(f"Eroare la {element} pe linia {line_number}")


def create_element(element: list[str]) -> str:
    element = "".join(char for char in element)
    element.strip()
    return element


def save_to_file():
    with open("tsc.txt", "w") as f:
        for element in ts_constants.data:
            f.write(f"{element}\n")

    with open("tsi.txt", "w") as f:
        for element in ts_identifiers.data:
            f.write(f"{element}\n")

    with open("fip.txt", "w") as f:
        for element in fip:
            f.write(f"Code: {element.code}; TSC: {element.pos_ts_c + 1 if element.pos_ts_c is not None else element.pos_ts_c};"
                    f" TSI: {element.pos_ts_i + 1 if element.pos_ts_i  is not None else element.pos_ts_i}\n")


def main():
    with open(filepath, "r") as f:
        line_number = 1
        while line := f.readline():
            line = list(x for x in line.strip())
            element = []
            index = 0
            while index < len(line):
                if line[index].isspace():
                    determine_type_element(line[index], line_number)
                    if element:
                        element = create_element(element)
                        determine_type_element(element, line_number)
                        element = []
                else:
                    if not line[index].isspace() and line[index] in ';,()':
                        line.insert(index + 1, ' ')
                        if element:
                            element = create_element(element)
                            determine_type_element(element, line_number)
                            element = []
                    element.append(line[index])

                index += 1
            line_number += 1

            if element:
                element = create_element(element)
                determine_type_element(element, line_number)

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
