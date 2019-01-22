def get_input():
    f = open('input', 'r')
    d = f.read()
    f.close()
    return d

def star1():
    d = get_input()
    garbage = False
    ignore = False
    value = 0
    total = 0
    for n in d:
        if not ignore:
            if n == '<':
                garbage = True
            elif n == '>':
                garbage = False
            elif n == '!' and garbage:
                ignore = True
        else:
            ignore = False    
        if not garbage:
            if n == '{':
                value += 1
            elif n == '}':
                total += value
                value -= 1
    return total

def star2():
    d = get_input()
    garbage = False
    ignore = False
    total = 0
    for n in d:
        if garbage and not ignore:
            total += 1
        if not ignore:
            if n == '<':
                garbage = True
            elif n == '>':
                garbage = False
                total -= 1
            elif n == '!' and garbage:
                ignore = True
                total -= 1
        else:
            ignore = False
    return total
