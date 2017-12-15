class Tree():
    def __init__(self, value, children):
        self.value = value
        self.children = children

nodes = []
        
def get_input():
    f = open('input', 'r')
    d = f.read()
    f.close()
    return d

def create_tree(l):
    global nodes
    nodes = [Tree(int(n), []) for n in range(len(l))]    
    for n in l:
        k = int(n.split(' ')[0])
        for c in n.split('>')[1].split(','):
            nodes[k].children.append(nodes[int(c)])
    return nodes[0]

tree_parsing = []

def parse_tree(t):
    global tree_parsing
    tree_parsing.append(t.value)
    for e in t.children:
        if e.value not in tree_parsing:
            parse_tree(e)

def find_groups():
    global nodes
    global tree_parsing
    lnodes = []
    total = 0
    for n in nodes:
        if n.value not in lnodes:
            tree_parsing = []
            total += 1
            parse_tree(n)
            lnodes += tree_parsing
    return total
            
def star1():
    global tree_parsing
    t = create_tree(get_input().split('\n'))
    parse_tree(t)
    return len(tree_parsing)

def star2():
    parse_tree(create_tree(get_input().split('\n')))
    return find_groups()
