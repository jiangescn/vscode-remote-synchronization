def inventory_pickup(inventory: list, items: list, capacity: int) -> list:
    """模拟逐一拾取 items 中的每个物品，并将它们原地添加到 inventory 中。
    此函数应返回修改后的 inventory。
    
    >>> inv = [1, 2, 1, 3, 1]
    >>> inv_test = inventory_pickup(inv, [1, 4], 10)
    >>> inv_test
    [2, 3, 1, 4]

    >>> inv2 = [11, 12, 13]
    >>> inv2_test = inventory_pickup(inv2, inv2, 7)
    >>> inv2_test
    [11, 12, 13]
    
    >>> inv3 = [1, 2, 1, 3, 1]
    >>> check_mutation = inv3
    >>> inv3_test = inventory_pickup(inv3, inv3, 3)
    >>> inv3_test
    [2, 3, 1]
    >>> check_mutation is inv3_test
    True
    
    >>> inv4 = [1, 2, 3, 4]
    >>> inv4_test = inventory_pickup(inv4, [5, 6, 7, 8, 9, 10], 10)
    >>> inv4_test
    [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    
    >>> inv5 = [1, 2, 3, 4]
    >>> inv5_test = inventory_pickup(inv5, [5, 6, 7, 8], 6)
    >>> inv5_test
    [3, 4, 5, 6, 7, 8]
    
    >>> inv6 = ['hello', 'world']
    >>> inv6_test = inventory_pickup(inv6, ['hi', 'hello'], 4)
    >>> inv6_test
    ['world', 'hi', 'hello']
    """
    "*** 在此处填写你的代码 ***"
    temp = tuple(items)
    for it in temp:
        while (it in inventory):
            inventory.remove(it)
        inventory.append(it)

    while (len(inventory) > capacity):
        inventory.pop(0)

    return inventory


def berry_finder(t):
    """如果 t 中包含值为 'berry' 的节点，则返回 True，
    否则返回 False。

    >>> scrat = tree('berry')
    >>> berry_finder(scrat)
    True
    >>> sproul = tree('roots', [tree('branch1', [tree('leaf'), tree('berry')]), tree('branch2')])
    >>> berry_finder(sproul)
    True
    >>> numbers = tree(1, [tree(2), tree(3, [tree(4), tree(5)]), tree(6, [tree(7)])])
    >>> berry_finder(numbers)
    False
    >>> t = tree(1, [tree('berry',[tree('not berry')])])
    >>> berry_finder(t)
    True
    """
    "*** 在此处填写你的代码 ***"
    ans = False
    for i in t:
        if(type(i) == list):
            ans = ans or berry_finder(i)
        else:
            if(i == 'berry'):
                ans = True

    return ans
            


def size_of_tree(t):
    """返回树中节点的数量。
    >>> numbers = tree(1, [tree(2), tree(3, [tree(4), tree(5)]), tree(6, [tree(7)])])
    >>> print_tree(numbers)
    1
      2
      3
        4
        5
      6
        7
    >>> size_of_tree(numbers)
    7
    """
    "*** 在此处填写你的代码 ***"
    ans = 0
    for i in t:
        if(type(i) == list):
            ans += size_of_tree(i)
        else:
            ans += 1
    return ans



def make_path(t, p):
    """返回一棵包含 t 的所有节点以及标签路径 p 的树。

    >>> t2 = tree(5, [tree(6), tree(7)])
    >>> t1 = tree(3, [tree(4), t2])
    >>> make_path(t1, [3, 5, 7]) == t1
    True
    >>> print_tree(make_path(t1, [3, 8, 9, 1]))
    3
      4
      5
        6
        7
      8
        9
          1
    >>> print_tree(make_path(t1, [3, 4, 8, 9]))
    3
      4
        8
          9
      5
        6
        7
    >>> print_tree(make_path(tree(2, [tree(1), t1]), [2, 3, 5, 6, 8]))
    2
      1
      3
        4
        5
          6
            8
          7
    """
    assert p[0] == label(t), '无法创建此路径'
    if len(p) == 1:
        return t
    new_branches = []
    found_p1 = False
    for b in branches(t):
        if not found_p1 and label(b) == p[1]:
            new_branches.append(make_path(b, p[1:]))
            found_p1 = True
        else:
            new_branches.append(b)
    if not found_p1:
        new_branches.append(make_path(p[1], p[1:]))
    return tree(label(t), new_branches)


def merge(incr_a, incr_b):
    """依次生成严格递增的可迭代对象 incr_a 和 incr_b 中的元素，并去除
    重复值。假设 incr_a 和 incr_b 本身都没有重复值。incr_a 或 incr_b
    可能是无限序列，也可能不是。

    >>> m = merge([0, 2, 4, 6, 8, 10, 12, 14], [0, 3, 6, 9, 12, 15])
    >>> type(m)
    <class 'generator'>
    >>> list(m)
    [0, 2, 3, 4, 6, 8, 9, 10, 12, 14, 15]
    >>> def big(n):
    ...    k = 0
    ...    while True: yield k; k += n
    >>> m = merge(big(2), big(3))
    >>> [next(m) for _ in range(11)]
    [0, 2, 3, 4, 6, 8, 9, 10, 12, 14, 15]
    """
    iter_a, iter_b = iter(incr_a), iter(incr_b)
    next_a, next_b = next(iter_a, None), next(iter_b, None)
    "*** 在此处填写你的代码 ***"
    while next_a is not None or next_b is not None:
        if next_a is None:
            yield next_b
            next_b = next(iter_b, None)

        elif next_b is None:
            yield next_a
            next_a = next(iter_a, None)

        elif next_a < next_b:
            yield next_a
            next_a = next(iter_a, None)

        elif next_b < next_a:
            yield next_b
            next_b = next(iter_b, None)

        else:
            yield next_a
            next_a = next(iter_a, None)
            next_b = next(iter_b, None)


def yield_paths(t, target):
    """
    依次生成从 t 的根节点到标签为 target 的节点的所有可能路径，
    每条路径以列表表示。

    >>> t1 = tree(1, [tree(2, [tree(3), tree(4, [tree(6)]), tree(5)]), tree(5)])
    >>> print_tree(t1)
    1
      2
        3
        4
          6
        5
      5
    >>> next(yield_paths(t1, 6))
    [1, 2, 4, 6]
    >>> path_to_5 = yield_paths(t1, 5)
    >>> sorted(list(path_to_5))
    [[1, 2, 5], [1, 5]]

    >>> t2 = tree(0, [tree(2, [t1])])
    >>> print_tree(t2)
    0
      2
        1
          2
            3
            4
              6
            5
          5
    >>> path_to_2 = yield_paths(t2, 2)
    >>> sorted(list(path_to_2))
    [[0, 2], [0, 2, 1, 2]]
    """
    if label(t) == target:
        yield [label(t)]

    for b in branches(t):
        for path in yield_paths(b, target):
            yield [label(t)] + path


passphrase = 'REPLACE_THIS_WITH_PASSPHRASE'

def midsem_survey(p):
    """
    你不需要理解这段代码。
    >>> midsem_survey(passphrase)
    '2bf925d47c03503d3ebe5a6fc12d479b8d12f14c0494b43deba963a0'
    """
    import hashlib
    return hashlib.sha224(p.encode('utf-8')).hexdigest()



# 树数据抽象

def tree(label, branches=[]):
    """使用给定的标签值和分支列表构造一棵树。"""
    for branch in branches:
        assert is_tree(branch), '分支必须是树'
    return [label] + list(branches)

def label(tree):
    """返回树的标签值。"""
    return tree[0]

def branches(tree):
    """返回给定树的分支列表。"""
    return tree[1:]

def is_tree(tree):
    """如果给定对象是一棵树，则返回 True，否则返回 False。"""
    if type(tree) != list or len(tree) < 1:
        return False
    for branch in branches(tree):
        if not is_tree(branch):
            return False
    return True

def is_leaf(tree):
    """如果给定树的分支列表为空，则返回 True，
    否则返回 False。
    """
    return not branches(tree)

def print_tree(t, indent=0):
    """打印这棵树的表示形式，其中每个节点按照其与根节点的深度，
    每层缩进两个空格。

    >>> print_tree(tree(1))
    1
    >>> print_tree(tree(1, [tree(2)]))
    1
      2
    >>> numbers = tree(1, [tree(2), tree(3, [tree(4), tree(5)]), tree(6, [tree(7)])])
    >>> print_tree(numbers)
    1
      2
      3
        4
        5
      6
        7
    """
    print('  ' * indent + str(label(t)))
    for b in branches(t):
        print_tree(b, indent + 1)

def copy_tree(t):
    """返回 t 的副本。仅供测试使用。

    >>> t = tree(5)
    >>> copy = copy_tree(t)
    >>> t = tree(6)
    >>> print_tree(copy)
    5
    """
    return tree(label(t), [copy_tree(b) for b in branches(t)])
