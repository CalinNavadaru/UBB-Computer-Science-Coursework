class Element:
    pass


class Terminal(Element):

    def __init__(self, value):
        self.value = value

    def __str__(self):
        return self.value


class Neterminal(Element):
    def __init__(self, value):
        self.value = value

    def __str__(self):
        return self.value


class Productie:
    def __init__(self, left: list[Element], right: list[Element]):
        self.left = left
        self.right = right

    def find_neterminal(self, value: Neterminal):
        for element in self.left:
            if isinstance(element, Neterminal) and element.value == value.value:
                return True

        for element in self.right:
            if isinstance(element, Neterminal) and element.value == value.value:
                return True

        return False

    def __str__(self):
        return f"{[x for x in self.left]} -> {[x for x in self.right]}"


def main():
    neterminale = []
    terminale = []
    productions = []
    with open("input.txt", "r") as f:
        elements = f.readline().strip().split(" ")
        for element in elements:
            neterminale.append(Neterminal(element))
        elements = f.readline().strip().split(" ")
        for element in elements:
            terminale.append(Terminal(element))
        while elements := f.readline().strip().split(" "):
            if elements == ['']:
                break
            left = []
            right = []
            i = 0
            for index, element in enumerate(elements):
                if element == '->':
                    i = index
                    break
                if element.isupper():
                    left.append(Neterminal(element))
                elif element.islower() or element == '@':
                    left.append(Terminal(element))

            for j in range(i + 1, len(elements)):
                if elements[j].isupper():
                    right.append(Neterminal(elements[j]))
                elif elements[j].islower() or element == '@':
                    right.append(Terminal(elements[j]))

            productions.append(Productie(left, right))

    input_value = Neterminal(input("Neterminal: "))
    for prod in productions:
        if prod.find_neterminal(input_value):
            print(f"{[str(x) for x in prod.left]} -> {[str(x) for x in prod.right]}")


main()
