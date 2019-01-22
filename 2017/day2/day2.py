def star2():
    f = open("input", "r")
    lines = f.readlines()
    f.close()
    total = 0
    for line in lines:
        line = line.split("\t")
        for n in line:
            for n1 in range(len(line)):
                n = int(n)
                n1 = int(line[n1])
                if (n % n1 == 0 and n != n1):
                  total = total + (n / n1)
                  break
    return total
