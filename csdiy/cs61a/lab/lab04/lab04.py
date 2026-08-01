def my_map(fn, seq):
    """将 fn 应用于 seq 中的每个元素，并返回一个列表。
    >>> my_map(lambda x: x*x, [1, 2, 3])
    [1, 4, 9]
    >>> my_map(lambda x: abs(x), [1, -1, 5, 3, 0])
    [1, 1, 5, 3, 0]
    >>> my_map(lambda x: print(x), ['cs61a', 'summer', '2023'])
    cs61a
    summer
    2023
    [None, None, None]
    """
    return [fn(seq[i]) for i in range(len(seq))]

def my_filter(pred, seq):
    """仅保留 seq 中满足 pred 的元素。
    >>> my_filter(lambda x: x % 2 == 0, [1, 2, 3, 4])  # 新列表中只有值为偶数的元素
    [2, 4]
    >>> my_filter(lambda x: (x + 5) % 3 == 0, [1, 2, 3, 4, 5])
    [1, 4]
    >>> my_filter(lambda x: print(x), [1, 2, 3, 4, 5])
    1
    2
    3
    4
    5
    []
    >>> my_filter(lambda x: max(5, x) == 5, [1, 2, 3, 4, 5, 6, 7])
    [1, 2, 3, 4, 5]
    """
    return [i for i in seq if pred(i)]

def my_reduce(combiner, seq):
    """使用 combiner 合并 seq 中的元素。
    seq 至少包含一个元素。
    >>> my_reduce(lambda x, y: x + y, [1, 2, 3, 4])  # 1 + 2 + 3 + 4
    10
    >>> my_reduce(lambda x, y: x * y, [1, 2, 3, 4])  # 1 * 2 * 3 * 4
    24
    >>> my_reduce(lambda x, y: x * y, [4])
    4
    >>> my_reduce(lambda x, y: x + 2 * y, [1, 2, 3]) # (1 + 2 * 2) + 2 * 3
    11
    """
    "*** 在此处编写代码 ***"
    ans = seq[0]
    for i in range(1, len(seq)):
        ans = combiner(ans, seq[i])
    return ans

def my_map_syntax_check():
    """检查你的 two_of_three 代码是否只包含一条 return 语句。

    >>> # 不要求你理解此测试的代码。
    >>> import inspect, ast
    >>> [type(x).__name__ for x in ast.parse(inspect.getsource(my_map)).body[0].body]
    ['Expr', 'Return']
    """
    # 你无需编辑此函数，它只用于检查你的代码。

def my_filter_syntax_check():
    """检查你的 two_of_three 代码是否只包含一条 return 语句。

    >>> # 不要求你理解此测试的代码。
    >>> import inspect, ast
    >>> [type(x).__name__ for x in ast.parse(inspect.getsource(my_filter)).body[0].body]
    ['Expr', 'Return']
    """
    # 你无需编辑此函数，它只用于检查你的代码。


from math import sqrt
def distance(city_a, city_b):
    """
    根据 city_a 和 city_b 的坐标返回两座城市之间的距离。

    >>> city_a = make_city('city_a', 0, 1)
    >>> city_b = make_city('city_b', 0, 2)
    >>> distance(city_a, city_b)
    1.0
    >>> city_c = make_city('city_c', 6.5, 12)
    >>> city_d = make_city('city_d', 2.5, 15)
    >>> distance(city_c, city_d)
    5.0
    """
    "*** 在此处编写代码 ***"
    lata = get_lat(city_a)
    latb = get_lat(city_b)
    lona = get_lon(city_a)
    lonb = get_lon(city_b)

    return sqrt(pow(lata - latb, 2) + pow(lona - lonb, 2))
    

def closer_city(lat, lon, city_a, city_b):
    """
    返回 city_a 或 city_b 中距坐标 (lat, lon) 更近的城市名称。
    如果两座城市距该坐标一样近，则将 city_b 视为更近的城市。

    >>> berkeley = make_city('Berkeley', 37.87, 112.26)
    >>> stanford = make_city('Stanford', 34.05, 118.25)
    >>> closer_city(38.33, 121.44, berkeley, stanford)
    'Stanford'
    >>> bucharest = make_city('Bucharest', 44.43, 26.10)
    >>> vienna = make_city('Vienna', 48.20, 16.37)
    >>> closer_city(41.29, 174.78, bucharest, vienna)
    'Bucharest'
    """
    "*** 在此处编写代码 ***"
    point = make_city('point', lat, lon)
    disa = distance(point, city_a)
    disb = distance(point, city_b)
    if (disa < disb):
        return get_name(city_a)
    else:
        return get_name(city_b)

def check_city_abstraction():
    """
    此函数无需你完成任何操作，它只是用于额外的 doctest。
    >>> change_abstraction(True)
    >>> city_a = make_city('city_a', 0, 1)
    >>> city_b = make_city('city_b', 0, 2)
    >>> distance(city_a, city_b)
    1.0
    >>> city_c = make_city('city_c', 6.5, 12)
    >>> city_d = make_city('city_d', 2.5, 15)
    >>> distance(city_c, city_d)
    5.0
    >>> berkeley = make_city('Berkeley', 37.87, 112.26)
    >>> stanford = make_city('Stanford', 34.05, 118.25)
    >>> closer_city(38.33, 121.44, berkeley, stanford)
    'Stanford'
    >>> bucharest = make_city('Bucharest', 44.43, 26.10)
    >>> vienna = make_city('Vienna', 48.20, 16.37)
    >>> closer_city(41.29, 174.78, bucharest, vienna)
    'Bucharest'
    >>> change_abstraction(False)
    """

# 将以下所有代码视为位于抽象层之后，
# 你不需要查看它们。
def make_city(name, lat, lon):
    """
    >>> city = make_city('Berkeley', 0, 1)
    >>> get_name(city)
    'Berkeley'
    >>> get_lat(city)
    0
    >>> get_lon(city)
    1
    """
    if change_abstraction.changed:
        return {"name" : name, "lat" : lat, "lon" : lon}
    else:
        return [name, lat, lon]

def get_name(city):
    """
    >>> city = make_city('Berkeley', 0, 1)
    >>> get_name(city)
    'Berkeley'
    """
    if change_abstraction.changed:
        return city["name"]
    else:
        return city[0]

def get_lat(city):
    """
    >>> city = make_city('Berkeley', 0, 1)
    >>> get_lat(city)
    0
    """
    if change_abstraction.changed:
        return city["lat"]
    else:
        return city[1]

def get_lon(city):
    """
    >>> city = make_city('Berkeley', 0, 1)
    >>> get_lon(city)
    1
    """
    if change_abstraction.changed:
        return city["lon"]
    else:
        return city[2]

###############


def sum_tree(t):
    """将树中的所有元素相加。

    >>> t = tree(4, [tree(2, [tree(3)]), tree(6)])
    >>> sum_tree(t)
    15
    """
    "*** 在此处编写代码 ***"

    return label(t) + sum(sum_tree(b) for b in branches(t))



def balanced(t):
    """检查每个分支的所有元素之和是否相同，
    以及每个分支是否平衡。

    >>> t = tree(1, [tree(3), tree(1, [tree(2)]), tree(1, [tree(1), tree(1)])])
    >>> balanced(t)
    True
    >>> t = tree(1, [t, tree(1)])
    >>> balanced(t)
    False
    >>> t = tree(1, [tree(4), tree(1, [tree(2), tree(1)]), tree(1, [tree(3)])])
    >>> balanced(t)
    False
    """
    "*** 在此处编写代码 ***"
    return (all(sum_tree(b) == sum_tree(branches(t)[0])for b in branches(t)) and all(balanced(b) for b in branches(t)))


def num_trees(n):
    """返回恰好有 n 个叶节点的不同满二叉树数量。例如：

    1   2        3       3    ...
    *   *        *       *
       / \\      / \\     / \\ 
      *   *    *   *   *   *
              / \\         / \\ 
             *   *       *   *

    >>> num_trees(1)
    1
    >>> num_trees(2)
    1
    >>> num_trees(3)
    2
    >>> num_trees(8)
    429

    """
    "*** 在此处编写代码 ***"
    if n == 1:
        return 1
    return sum(num_trees(k) * num_trees(n - k)for k in range(1, n))


def only_paths(t, n):
    """返回一棵树，它只保留 t 中从根节点到叶节点且路径上
    节点标签之和为 n 的路径节点。如果没有路径的和为 n，则返回 None。

    >>> print_tree(only_paths(tree(5, [tree(2), tree(1, [tree(2)]), tree(1, [tree(1)])]), 7))
    5
      2
      1
        1
    >>> t = tree(3, [tree(4), tree(1, [tree(3, [tree(2)]), tree(2, [tree(1)]), tree(5), tree(3)])])
    >>> print_tree(only_paths(t, 7))
    3
      4
      1
        2
          1
        3
    >>> print_tree(only_paths(t, 9))
    3
      1
        3
          2
        5
    >>> print(only_paths(t, 3))
    None
    """
    # if ____:
    #     return t
    # new_branches = [____ for b in branches(t)]
    # if ____(new_branches):
    #     return tree(label(t), [b for b in new_branches if ____])




# 树的数据抽象

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
    """如果给定的 tree 是树，则返回 True；否则返回 False。"""
    if type(tree) != list or len(tree) < 1:
        return False
    for branch in branches(tree):
        if not is_tree(branch):
            return False
    return True

def is_leaf(tree):
    """如果给定树的分支列表为空，则返回 True；否则返回 False。
    """
    return not branches(tree)

def print_tree(t, indent=0):
    """打印此树的文本表示，每个节点的缩进空格数等于
    它距根节点的深度乘以 2。

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
    """返回 t 的一份副本，仅用于测试。

    >>> t = tree(5)
    >>> copy = copy_tree(t)
    >>> t = tree(6)
    >>> print_tree(copy)
    5
    """
    return tree(label(t), [copy_tree(b) for b in branches(t)])
def change_abstraction(change):
    """
    用于测试。
    >>> change_abstraction(True)
    >>> change_abstraction.changed
    True
    """
    change_abstraction.changed = change

change_abstraction.changed = False

