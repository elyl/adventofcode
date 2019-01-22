def star1():
    f = open("input", "r")
    lines = f.readlines()
    f.close()
    total = 0
    for line in lines:
        ok = True
        line = line.replace('\n', '')
        line = line.split(" ")
        for word in line:
            if line.count(word) > 1:
                ok = False
                break
        total = total + (1 if ok else 0)
    return total

def star2():
    f = open("input", "r")
    lines = f.readlines()
    f.close()
    total = 0
    for line in lines:
        line = line.replace("\n", "")
        line = line.split(" ")
        ok = True
        for i in range(len(line)):
            w1 = line[i]
            c1 = [0] * 26
            for c in w1:
                c1[ord(c) - ord('a')] += 1
            for j in range(i + 1, len(line)):
                w2 = line[j]
                c2 = [0] * 26
                for c in w2:
                    c2[ord(c) - ord('a')] += 1
                if c1 == c2:
                    ok = False
                    break
        total += 1 if ok else 0
    return total
