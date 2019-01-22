def star1():
    depth = 10647
    target = [7, 770]
    cave = [[0] * (target[1] + 1)] * (target[0] + 1)
    erosion = [[0] * (target[1] + 1)] * (target[0] + 1)
    risk = 0
    for x in range(target[0] + 1):
        for y in range(target[1] + 1):
            if x == 0 or y == 0:
                cave[x][y] = 48271 * y + 16807 * x
            elif x == target[0] and y == target[1]:
                cave[x][y] = 0
            else:
                cave[x][y] = erosion[x - 1][y] * erosion[x][y - 1];
            erosion[x][y] = (cave[x][y] + depth) % 20183
            risk += erosion[x][y] % 3
    return risk

print(star1())
