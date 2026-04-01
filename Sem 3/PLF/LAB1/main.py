i = 1


def f(a, b):
    global i
    print(f"Iteratia = {i}\na = {a}\nb = {b}\n")
    i = i + 1
    if b == 0:
        return a

    return f(b, a % b)


print(f(15, 25))
