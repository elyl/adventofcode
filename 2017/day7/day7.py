def get_file():
    f = open('input', 'r')
    raw = f.read().split('\n')
    f.close()
    return raw

def star1():
    raw = get_file()
    towers = []
    towers2 = []
    for e in raw:
        towers.append(e.split(' ')[0])
        if '>' in e:
            tmp = e.split('>')[1].replace(' ', '').split(',')
            for z in tmp:
                towers2.append(z)
    for t in towers:
        if t not in towers2:
            return t

class Tree():
    def __init__(self, name, value):
        self.name = name
        self.value = value
        self.children = []

    def __str__(self):
        return self.name + ' :' + self.value

def create_tree(data):
    elements = []
    names = []
    for n in data:
        s = n.split(' ')
        w = int(n[n.index('(') + 1:n.index(')')])
        if s[0] in names:
            element = find_in_tree(elements, s[0])
            element.value = w
        else:
            element = Tree(s[0], w)
            elements.append(element)
        names.append(s[0])
        if '>' in n:
            children_names = n.split('>')[1].replace(' ', '').split(',')
            for c in children_names:
                if c not in names:
                    t = Tree(c, 0)
                    elements.append(t)
                else:
                    t = find_in_tree(elements, c)
                names.append(c)
                element.children.append(t)
    return get_base(names, elements)

def find_in_tree(elements, name):
    for e in elements:
        if e.name == name:
            return e
    return None

def get_base(names, elements):
    for n in names:
        if names.count(n) == 1:
            return find_in_tree(elements, n)

def get_weight(base):
    w = base.value
    for e in base.children:
        w += get_weight(e)
    return (w)

def star2():
    f = open('input', 'r')
    data = f.read().split('\n')
    f.close()
    base = create_tree(data)
    w = []
    for e in base.children[1].children[0].children:
        w.append(get_weight(e))
    return base.children[1].children[0].children[2].value
