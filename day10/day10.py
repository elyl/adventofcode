def get_input():
    f = open('input', 'r')
    d = f.read()
    f.close()
    return d[:-1] if d[-1] == '\n' else d

def convert_input(n):
    return [ord(c) for c in str(n)]

def star1():
    global skip, i, l
    l = [n for n in range(256)]
    skip = i = 0
    d = [int(n) for n in get_input().split(',')]
    l = do_hash(d)
    return l[0] * l[1]

def star2():
    global skip, i, l
    skip = i = 0
    d = []
    for z in [convert_input(n) for n in get_input()]:
        d += z
    d += [17, 31, 73, 47, 23]
    l = [n for n in range(256)]
    for n in range(64):
        do_hash(d)
    h = [format(dense_hash(l[(n*16):(n*16)+16]), 'x') for n in range(16)]
    s = ''
    for k in h:
        if len(k) == 1:
            s += '0'
        s += k
    return s

def dense_hash(numbers):
    k = 0
    for n in numbers:
        k ^= n
    return k

def do_hash(d):
    global skip, i, l
    global i
    for n in d:
        l = reverse(l, i, n)
        i += (n + skip) % 256
        skip += 1
    return l

def reverse(l, start, count):
    size = 256
    for i in range(count // 2):
        if i == 0:
            fst = (start) % size
            snd = (start + count - 1) % size
        else:
            fst = (fst + 1) % size
            snd = (snd - 1) % size
        tmp = l[fst]
        l[fst] = l[snd]
        l[snd] = tmp
    return l
