class Register():
    def __init__(self, name):
        self.name = name
        self.value = 0

registers_list = []
registers_name = []
val = []
        
def get_register(name):
    if name not in registers_name:
        r = Register(name)
        registers_name.append(name)
        registers_list.append(r)
    else:
        for r in registers_list:
            if r.name == name:
                break
    return r

def parse_action(action):
    details = action.split(' ')
    r_name = details[0]
    r = get_register(r_name)
    if eval(str(get_register(details[4]).value) + details[5] + details[6]):
        if details[1] == 'inc':
            r.value += int(details[2])
        else:
            r.value -= int(details[2])
        val.append(r.value)
        
def star1():
    f = open('input', 'r')
    actions = f.read().split('\n')
    f.close()
    for a in actions:
        parse_action(a)
    valmax = 0
    for r in registers_list:
        valmax = r.value if r.value > valmax else valmax
    return valmax

def star2():
    star1()
    return max(val)
