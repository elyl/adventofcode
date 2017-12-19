def get_input():
    f = open('input', 'r')
    d = f.read().split(',')
    f.close()
    return d

def spin(l, nb):
    return l[-nb:] + l[:-nb]

def swap(l, a, b):
    tmp = l[a]
    l[a] = l[b]
    l[b] = tmp
    return l

entities = [chr(c) for c in range(ord('a'), ord('q'))]
data_in = get_input()

def star1():
    global entities
    global data_in
    for a in data_in:
        e = a.split('/')
        if a[0] == 's':
            entities = spin(entities, int(a[1:]))
        elif a[0] == 'x':
            entities = swap(entities, int(e[0][1:]), int(e[1]))
        elif a[0] == 'p':
            entities = swap(entities, entities.index(e[0][1:]), entities.index(e[1]))
        else:
            print ('error')
    return entities

def star2():
    global entities
    ref = entities.copy()
    n = 0
    while True:
        star1()
        n += 1
        if entities == ref:
            break
    t = 1000000000 % n
    entities = ref
    for n in range(t):
        star1()
    return entities
