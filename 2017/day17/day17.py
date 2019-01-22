def star1():
    steps = 345
    b = [0]
    pos = 0
    for n in range(1, 2018):
        pos += steps
        pos %= len(b)
        b = b[:pos + 1] + [n] + b[pos + 1:]
        pos += 1
    return b[b.index(2017) + 1]

def star2():
    steps = 345
    pos = 0
    final = 0
    for n in range(1, 50000000):
        pos += steps
        pos %= n
        pos += 1
        if pos == 1:
            final = n
    return final
                                            
