def get_input():
    f = open('input', 'r')
    d = f.read()
    f.close()
    return d[:-1] if d[-1] == '\n' else d

def convert_input(n):
    return [ord(c) for c in str(n)]

def knot_hash(offset):
    global skip, i, l
    skip = i = 0
    d = []
    for z in [convert_input(n) for n in get_input() + '-' + str(offset)]:
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

def star1():
    rows = [knot_hash(n) for n in range(128)]
    count = 0
    for z in rows:
        for k in z:
            k = int(k, 16)
            if k & 8:
                count += 1
            if k & 4:
                count += 1
            if k & 2:
                count += 1
            if k & 1:
                count += 1
    return count

grid = [[0 for n in range(128)] for n in range(128)]

def convert_result():
    global grid
    rows = [knot_hash(n) for n in range(128)]
    for z in range(128):
        for k in range(32):
            n = int(rows[z][k], 16)
            if n & 8:
                grid[z][k * 4] = 1
            if n & 4:
                grid[z][k * 4 + 1] = 1
            if n & 2:
                grid[z][k * 4 + 2] = 1
            if n & 1:
                grid[z][k * 4 + 3] = 1
    
def count_groups():
    global grid
    count = 0
    for row in range(128):
        for col in range(128):
            if grid[row][col] == 1:
                count += 1
                clean_group(row, col)                
    return count

def clean_group(row, col):
    global grid
    if grid[row][col] == 1:
        grid[row][col] = 0
        if row < 127:
            clean_group(row + 1, col)
        if col < 127:
            clean_group(row, col + 1)
        if col > 0:
            clean_group(row, col - 1)
        if row > 0:
            clean_group(row - 1, col)

def star2():
    global grid
    convert_result()
    return count_groups()
