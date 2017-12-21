def get_input():
    f = open('input', 'r')
    d = f.read().split('\n')
    f.close()
    return d

registers = [[0 for n in range(ord('z') - ord('a'))], [0 for n in range(ord('z') - ord('a'))]]

def star1():
    global registers
    inst = get_input()
    n = 0
    snd = 0
    while n < len(inst):
        b = inst[n].split(' ')
        v1 = registers[ord(b[1]) - ord('a')] if str.isalpha(b[1]) else int(b[1])
        if len(b) > 2:
            v2 = registers[ord(b[2]) - ord('a')] if str.isalpha(b[2]) else int(b[2])
        if b[0] == 'set':
            registers[ord(b[1]) - ord('a')] = v2
        elif b[0] == 'add':
            registers[ord(b[1]) - ord('a')] += v2
        elif b[0] == 'mul':
            registers[ord(b[1]) - ord('a')] *= v2
        elif b[0] == 'mod':
            registers[ord(b[1]) - ord('a')] %= v2
        elif b[0] == 'rcv':
            if v1 != 0:
                return snd
        elif b[0] == 'snd':
            snd = v1
        elif b[0] == 'jgz':
            n += v2 if v1 > 0 else 1
            continue
        else:
            print('bad instruction')
        n += 1
       
def star2():
    global registers
    w = [False, False]
    f = [[], []]
    inst = get_input()
    n = [0, 0]
    cnt = 0
    p = 0
    registers[1][ord('p') - ord('a')] = 1
    while True:
        b = inst[n[p]].split(' ')
        v1 = registers[p][ord(b[1]) - ord('a')] if str.isalpha(b[1]) else int(b[1])
        if len(b) > 2:
            v2 = registers[p][ord(b[2]) - ord('a')] if str.isalpha(b[2]) else int(b[2])
        if b[0] == 'set':
            registers[p][ord(b[1]) - ord('a')] = v2
        elif b[0] == 'add':
            registers[p][ord(b[1]) - ord('a')] += v2
        elif b[0] == 'mul':
            registers[p][ord(b[1]) - ord('a')] *= v2
        elif b[0] == 'mod':
            registers[p][ord(b[1]) - ord('a')] %= v2
        elif b[0] == 'rcv':
            if len(f[p]) > 0:
                registers[p][ord(b[1]) - ord('a')] = f[p][0]
                del(f[p][0])
                w[p] = False
            elif w[0] and w[1]:
                return cnt
            else:
                w[p] = True
                p = (p + 1) % 2
                continue
        elif b[0] == 'snd':
            f[(p + 1) % 2].append(v1)
            if p == 1:
                cnt += 1
            print (p, f)
        elif b[0] == 'jgz':
            n[p] += v2 if v1 > 0 else 1
            continue
        else:
            print('bad instruction')
        n[p] += 1
        p = (p + 1) % 2
