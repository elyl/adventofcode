from string import ascii_uppercase

def get_input():
    f = open('input', 'r')
    d = f.read().split('\n')
    f.close()
    return d

def find_start(data):
    x = y = 0
    for y in range(len(data[x])):
        if data[x][y] == '|':
            return x, y
        y += 1

def move_down(x, y, data):
    global steps
#    print('Going down now !')
    while data[x][y] != '+' and data[x][y] != end:
 #       print('down: ' + data[x][y] + ';x :' + str(x))
        if data[x][y] in ascii_uppercase:
            print(data[x][y])
        x += 1
        steps += 1
    return x, y

def move_up(x, y, data):
    global steps
#    print('Going up now !')
    while data[x][y] != '+' and data[x][y] != end:
#        print('up: ' + data[x][y])
        if data[x][y] in ascii_uppercase:
            print(data[x][y])
        steps += 1
        x -= 1
    return x, y

def move_right(x, y, data):
    global steps
#    print('Going right now !')
    while data[x][y] != '+' and data[x][y] != end :
#        print('Right : ' + data[x][y])
        if data[x][y] in ascii_uppercase:
            print(data[x][y])
        y += 1
        steps += 1
    return x, y

def move_left(x, y, data):
    global steps
#    print('Going left now !')
    while data[x][y] != '+' and data[x][y] != end:
#        print('Left : ' + data[x][y])
        if data[x][y] in ascii_uppercase:
            print(data[x][y])
        y -= 1
        steps += 1
    return x, y

steps = 0

def star1():
    global end, steps
    end = 'T'
    data = get_input()
    x, y = find_start(data)
    width = len(data[0])
    height = len(data)
    print(height, width)
    print('start :' + str(x) + ',' + str(y))
    direction = 'down'
    while data[x][y] != end:
#    for n in range(30): 
        if direction == 'down':
            if x != 0:
                x += 1
            x, y = move_down(x, y, data)
            direction = 'right' if y + 1 < width and data[x][y + 1] != ' ' else 'left'
        elif direction == 'up':
            x -= 1
            x, y = move_up(x, y, data)
            direction = 'right' if y + 1 < width and data[x][y + 1] != ' ' else 'left'
        elif direction == 'left':
            y -= 1
            x, y = move_left(x, y, data)
            direction = 'down' if x + 1 < height and data[x + 1][y] != ' ' else 'up'
        elif direction == 'right':
            y += 1
            x, y = move_right(x, y, data)
            direction = 'down' if x + 1 < height and data[x + 1][y] != ' ' else 'up'
        steps += 1

def star2():
    global steps
    star1()
    return steps
