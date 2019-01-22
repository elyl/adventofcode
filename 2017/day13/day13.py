def get_input():
    f = open('input', 'r')
    d = f.read().split('\n')
    l = [0] * (int(d[-1].split(':')[0]) + 1)
    for n in d:
        l[int(n.split(':')[0])] = int(n.split(':')[1])
    f.close()
    return l

def star1():
    l = get_input()
    return risk(0, l)

flag = False

def risk(delay, l):
    global flag
    v = 0
    for n in range(len(l)):
        mod = max(1, (l[n] - 1) * 2)
        if (n + delay) == 0 or (n + delay) % mod == 0:
            v += n * l[n]
            if n == 0:
                flag = True
    return v

def star2():
    global flag
    i = 0
    l = get_input()
    while True:
        flag = False
        if risk(i, l) == 0 and not flag:
            return i
        i += 1
