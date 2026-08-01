"用于文件和字符串操作的工具函数"

import string
from math import sqrt

##################
# 字符串工具函数 #
##################

def lines_from_file(path):
    """返回字符串列表，其中每个字符串对应文件中的一行。"""
    with open(path, 'r') as f:
        return [line.strip() for line in f.readlines()]

def remove_punctuation(s):
    """返回与 s 内容相同但移除了标点符号的字符串。

    >>> remove_punctuation("It's a lovely day, don't you think?")
    'Its a lovely day dont you think'
    >>> remove_punctuation("Its a lovely day dont you think")
    'Its a lovely day dont you think'
    """
    punctuation_remover = str.maketrans('', '', string.punctuation)
    return s.strip().translate(punctuation_remover)

def lower(s):
    """返回 s 的小写形式。

    >>> lower("HELLO")
    'hello'
    >>> lower("World")
    'world'
    >>> lower("hello WORLD")
    'hello world'
    """
    return s.lower()

def split(s):
    """返回 s 中包含的单词列表；单词是由空白字符
    （空格、制表符等）分隔的字符序列。

    >>> split("It's a lovely day, don't you think?")
    ["It's", 'a', 'lovely', 'day,', "don't", 'you', 'think?']
    """
    return s.split()

##################
# 键盘布局工具函数 #
##################

KEY_LAYOUT = [["1","2","3","4","5","6","7","8","9","0","-","="],
              ["q", "w", "e", "r", "t", "y", "u", "i", "o", "p","[","]"],
              ["a", "s", "d", "f", "g", "h", "j", "k", "l",";","'"],
              ["z", "x", "c", "v", "b", "n", "m",",",".","/"],
              [" "]]

def distance(p1, p2):
    """返回两点之间的欧几里得距离。

    两点 (x1, y1) 和 (x2, y2) 之间的欧几里得距离为
    (x1 - x2) ** 2 + (y1 - y2) ** 2 的平方根。

    >>> distance((0, 1), (1, 1))
    1.0
    >>> distance((1, 1), (1, 1))
    0.0
    >>> round(distance((4, 0), (0, 4)), 3)
    5.657
    """
    return sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)

def get_key_distances():
    """返回一个将按键对映射到距离的新字典。

    字典的每个键都是由两个字母字符串组成的元组，
    每个值都是这两个字母在标准 QWERTY 键盘上的
    归一化欧几里得距离。

    缩放比例保持不变，因此一对按键的实际距离如果是
    另一对的两倍，其距离值也会是另一对的两倍。

    >>> distances = get_key_distances()
    >>> distances["a", "a"]
    0.0
    >>> round(distances["a", "d"],3)
    1.367
    >>> round(distances["d", "a"],3)
    1.367
    """
    key_distance = {}

    def compute_pairwise_distances(i, j, d):
        for x in range(len(KEY_LAYOUT)):
            for y in range(len(KEY_LAYOUT[x])):
                l1 = KEY_LAYOUT[i][j]
                l2 = KEY_LAYOUT[x][y]
                d[l1, l2] = distance((i, j), (x, y))

    for i in range(len(KEY_LAYOUT)):
        for j in range(len(KEY_LAYOUT[i])):
            compute_pairwise_distances(i, j, key_distance)

    max_value = max(key_distance.values())
    return {key : value * 8 / max_value for key, value in key_distance.items()}

def count(f):
    """使用变量 call_count 记录函数 f 被调用的次数。

    >>> def factorial(n):
    ...     if n <= 1:
    ...         return 1
    ...     return n * factorial(n - 1)
    >>> factorial = count(factorial)
    >>> factorial(5)
    120
    >>> factorial.call_count
    5
    """
    def counted(*args):
        counted.call_count += 1
        return f(*args)
    counted.call_count = 0
    return counted

############
# 其他函数 #
############

def deep_convert_to_tuple(sequence):
    """将嵌套的列表和元组递归转换为元组。
    >>> deep_convert_to_tuple(5)
    5
    >>> deep_convert_to_tuple([2, 'hi'])
    (2, 'hi')
    >>> deep_convert_to_tuple([['These', 'are', 'all'], ['tuples.']])
    (('These', 'are', 'all'), ('tuples.',))
    """
    if isinstance(sequence, list) or isinstance(sequence, tuple):
        return tuple(deep_convert_to_tuple(item) for item in sequence)
    else:
        return sequence
