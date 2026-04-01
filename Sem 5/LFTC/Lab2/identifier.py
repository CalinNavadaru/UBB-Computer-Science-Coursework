import os.path
import string
import sys

if len(sys.argv) < 2:
    print("You must provide a MLP filepath! Exiting with error -1", file=sys.stderr, flush=True)
    sys.exit(-1)

filepath = sys.argv[1]

if not os.path.isfile(filepath):
    print("The provided path is invalid! Exiting with error -2", file=sys.stderr, flush=True)
    sys.exit(-2)

KEYWORDS_SET = {"cin", "cout", "struct", "for", "while", "if", "int", "float", "str", "struct"}
OPERATORS_SET = {"+", "-", "*", "/", "**", "%", "//", "&&", "||", "<", ">", "<=", ">=", "==", "!=", "<<", ">>", "="}
SEPARATORS_SET = {"{", "}", ";", ",", "'", "(", ")"} | set(string.whitespace)
identifiers = set()
constants = set()
keywords = set()
operators = set()
separators = set()


def is_string_constant(element: str):
    if element[0] != '\'' or element[-1] != '\'':
        return False
    return True


def is_decimal_number(element: str):
    return element.isdigit()


def is_octal_number(element: str):
    if not element[0] == 'O':
        return False

    return len(element) > 1 and all(0 <= int(digit) <= 7 for digit in element[1:])


def is_hexa_number(element: str):
    if not element[0:2] == 'OX':
        return False

    return len(element) > 2 and all('A' <= digit <= 'F' or 0 <= int(digit) <= 9 for digit in element[2:])


def is_binary_number(element):
    if not element[0] == 'b':
        return False

    return len(element) > 1 and all(0 <= int(digit) <= 1 for digit in element[1:])


def is_float_number(element):
    integer = []
    fraction = []
    has_point = False
    for e in element:
        if e == '.':
            has_point = True
            continue
        if not has_point:
            integer.append(e)
        else:
            fraction.append(e)

    integer = "".join(e for e in integer)
    fraction = "".join(e for e in fraction)
    return has_point and is_number(integer) and is_number(fraction)


def is_number(element: str):
    return len(element) > 0 and (is_decimal_number(element) or is_hexa_number(element) or is_octal_number(element)
                                 or is_binary_number(element) or is_float_number(element))


def determine_type_element(element: str) -> None:
    if element in SEPARATORS_SET:
        separators.add(element)
    elif element in KEYWORDS_SET:
        keywords.add(element)
    elif element in OPERATORS_SET:
        operators.add(element)
    elif is_number(element) or is_string_constant(element):
        constants.add(element)
    else:
        identifiers.add(element)


def create_element(element: list[str]) -> str:
    element = "".join(char for char in element)
    element.strip()
    return element


def main():
    with open(filepath, "r") as f:
        line = "placeholder"
        while line := f.readline():
            line = list(x for x in line.strip())
            element = []
            index = 0
            while index < len(line):
                if line[index].isspace():
                    determine_type_element(line[index])
                    if element:
                        element = create_element(element)
                        determine_type_element(element)
                        element = []
                else:
                    if not line[index].isspace() and line[index] in ';,()':
                        line.insert(index + 1, ' ')
                        if element:
                            element = create_element(element)
                            determine_type_element(element)
                            element = []
                    element.append(line[index])

                index += 1

            if element:
                element = create_element(element)
                determine_type_element(element)

    print(f"Identificatori: {set(sorted(identifiers))}", end='\n')
    print(f"Separatori: {set(sorted(separators))}", end='\n')
    print(f"Cuvinte-cheie: {set(sorted(keywords))}", end='\n')
    print(f"Operatori: {set(sorted(operators))}", end='\n')
    print(f"Constante: {set(sorted(constants))}", end='\n')


main()
