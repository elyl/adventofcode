def get_input():
    f = open('input', 'r')
    d = f.read().replace('=<', '').replace('>', '').replace('a', '').replace('p', ''). replace('v', '').split('\n')
    f.close()        
    return d

def parse_input(d):
    l = []
    for n in range(len(d)):
        s = d[n].split(',')
        l.append([[int(s[0]), int(s[1]), int(s[2])], [int(s[3]), int(s[4]), int(s[5])], [int(s[6]), int(s[7]), int(s[8])]])
    return l

def star1():
    data = parse_input(get_input())
    for n in range(1000):
        for k in data:
            k[1][0] += k[2][0]
            k[1][1] += k[2][1]
            k[1][2] += k[2][2]
            k[0][0] += k[1][0]
            k[0][1] += k[1][1]
            k[0][2] += k[1][2]
    m = []
    for k in data:
        m.append(abs(k[0][0]) + abs(k[0][1]) + abs(k[0][2]))
    return m.index(min(m))

def remove_particles(d, r):
    r = list(set(r))
#    print(r)
    k = 0
    for n in r:
        del d[n - k]
        k += 1
    return d

def star2():
    data = parse_input(get_input())
    for n in range(1000):
        r = []
        for n2 in range(len(data)):
            for n1 in range(n2 + 1, len(data)):
                if data[n2][0][0] == data[n1][0][0] and data[n2][0][1] == data[n1][0][1] and data[n2][0][2] == data[n1][0][2]:
                    r.append(n1)
                    r.append(n2)
#        print('removing')
        data = remove_particles(data, r)
#        print(n, len(data))
        for k in data:
            k[1][0] += k[2][0]
            k[1][1] += k[2][1]
            k[1][2] += k[2][2]
            k[0][0] += k[1][0]
            k[0][1] += k[1][1]
            k[0][2] += k[1][2]
    return len(data)
