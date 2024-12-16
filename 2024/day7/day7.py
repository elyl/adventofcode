import sys
from itertools import product
from operator import add, mul, concat


def solve(v, l, include_concat=False):
    ops = (
        product([add, mul], repeat=len(l) - 1)
        if not include_concat
        else product([add, mul, concat], repeat=len(l) - 1)
    )
    for o in ops:
        _v = 0
        for n in range(len(l) - 1):
            f, a, b = o[n], l[n] if n == 0 else _v, l[n + 1]
            _v = int(concat(str(a), str(b))) if o[n] == concat else o[n](a, b)
        if _v == v:
            return True
    return False


data = open("input").read().strip()

p1 = p2 = 0
for line in data.split("\n"):
    value = int(line.split(": ")[0])
    nums = [int(n) for n in line.split(": ")[1].split(" ")]
    p1 += value if solve(value, nums) else 0
    p2 += value if solve(value, nums, True) else 0
 #   if solve(value, nums):
 #       print(value)

print(f"Part 1: {p1}")
#print(f"Part 2: {p2}")
