def star1():
    gena = 116
    genb = 299
    count = 0
    for n in range(40000000):
        gena *= 16807
        genb *= 48271
        gena %= 2147483647
        genb %= 2147483647
        if (gena & 65535) == (genb & 65535):
            count += 1
    return count

def star2():
    gena = 116
    genb = 299
    count = 0
    for n in range(5000000):
        while gena % 4 != 0:
            gena *= 16807
            gena %= 2147483647
        while genb % 8 != 0:
            genb *= 48271
            genb %= 2147483647
        if (gena & 65535) == (genb & 65535):
            count += 1
    return count
