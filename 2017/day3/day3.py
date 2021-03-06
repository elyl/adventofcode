from math import *

def load_file():
    f = open("input", 'r')
    l = f.readlines()
    f.close()
    return l[0]

def closest_square(n):
    x1 = closest_se(n)
    x2 = closest_sw(n)
    x3 = closest_ne(n)
    x4 = closest_nw(n)
    x = x1 if min(x1[0], x2[0]) == x1[0] else x2
    x = x if min(x[0], x3[0]) == x[0] else x3
    x = x if min(x[0], x4[0]) == x[0] else x4
    return x
    

def closest_nw(n):
    x = 1
    x1 = 0
    s = 0
    while x < n:
        x1 = x
        x = pow(s, 2) + 1
        s += 2
    s = s // 2
    return min(n - x1, x - n), s

def closest_sw(n):
    x = 1
    x1 = 0
    s = 1
    while x < n:
        x1 = x
        x = pow(s, 2) - s + 1
        s += 2
    s = s // 2 - 1
    return min(n - x1, x - n), s

def closest_se(n):
    x = 1
    x1 = 0
    s = 0
    while x < n:
        x1 = x
        x = pow(2 * s + 1,  2)
        s += 1
    return min(n - x1, x - n), s

def closest_ne(n):
    x = 1
    x1 = 0
    s = 0
    while x < n:
        x1 = x
        x = pow(s, 2) - s + 1
        s += 2
    s = s // 2 - 1
    return min(n - x1, x - n), s 
        
def star1():
    target = int(load_file())
    n, steps = closest_square(target)
    return steps * 2+ n
    
def star2():
    return 0
