def star1(digits):
    total = 0
    n1 = 0
    for n in digits:
        n = int(n)
        if n1 == n:
            total += n1
        n1 = n
    if n == int(digits[0]):
            total += n
    return total    

def star2(digits):
    total = 0
    i = 0
    size = len(digits)
    for n in digits:
        n = int(n)
        if (n == int(digits[(i + int(size / 2)) % size])):
            total += n
        i += 1
    return total



