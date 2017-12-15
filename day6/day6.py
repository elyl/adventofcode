def star1():
    f = open('input', 'r')
    l = []
    banks = f.read().split('\t')
    f.close()
    size = len(banks)
    for n in range(size):
        banks[n] = int(banks[n])
    c = 0
    while banks not in l:
        l.append(list(banks))
        n = banks.index(max(banks))
        k = banks[n]
        banks[n] = 0
        while k > 0:
            n += 1
            banks[n % size] += 1
            k -= 1
        c += 1
    return c
            
def star2():
    f = open('input', 'r')
    l = []
    banks = f.read().split('\t')
    f.close()
    size = len(banks)
    for n in range(size):
        banks[n] = int(banks[n])
    c = 0
    flag = False
    while banks not in l:
        l.append(list(banks))
        n = banks.index(max(banks))
        k = banks[n]
        banks[n] = 0
        while k > 0:
            n += 1
            banks[n % size] += 1
            k -= 1
        c += 1
        if (banks in l and not flag):
            c = 0
            flag = True
            l = []
    return c
            
