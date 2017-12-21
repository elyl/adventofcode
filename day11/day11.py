def get_input():
    f = open('input', 'r')
    d = f.read().replace(' ', '').split(',')
    f.close()
    return d

def star1():
    d = get_input()
    n = d.count('n')
    s = d.count('s')
    e = d.count('e')
    w = d.count('w')
    ne = d.count('ne')
    nw = d.count('nw')
    se = d.count('se')
    sw = d.count('sw')
    
    if se > nw:
        se -= nw
        nw = 0
    else:
        nw -= se
        se = 0
    if ne > sw:
        ne -= sw
        sw = 0
    else:
        sw -= ne
        ne = 0
    if s > n:
        s -= n
        n = 0
    else:
        n -= s
        s = 0
    if e > w:
        e -= w
        w = 0
    else:
        w -= e
        e = 0


    k = min(n, e)
    sw -= k
    n -= k
    e -= k
    k = min(s, w)    
    ne -= k
    s -= k
    w -= k
    k = min(s, e)
    nw -= k
    s -= k
    e -= k
    k = min(n, w)
    se -= k
    n -= k
    w -= k
    
    return e + w + s + n + ne + nw + se + sw
