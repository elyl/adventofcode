def star1():
    f = open("input", "r")
    l = f.read().split('\n')
    i = 0
    size = len(l)
    n = 0
    for i in range(size):
        l[i] = int(l[i])
    i = 0
    while i >= 0 and i < size:
        tmp = l[i]
        l[i] += 1
        i += tmp
        n += 1
    return n

def star1():
    f = open("input", "r")
    l = f.read().split('\n')
    i = 0
    size = len(l)
    n = 0
    for i in range(size):
        l[i] = int(l[i])
    i = 0
    while i >= 0 and i < size:
        tmp = l[i]
        l[i] += -1 if l[i] >= 3 else 1
        i += tmp
        n += 1
    return n
