SOURCE_FILE = __file__


def num_eights(num: int) -> int:
    """返回数字 8 在 num 的各位中出现的次数。

    >>> num_eights(3)
    0
    >>> num_eights(8)
    1
    >>> num_eights(88888888)
    8
    >>> num_eights(2638)
    1
    >>> num_eights(86380)
    2
    >>> num_eights(12345)
    0
    >>> num_eights(8782089)
    3
    >>> from construct_check import check
    >>> # 禁止使用所有赋值语句
    >>> check(SOURCE_FILE, 'num_eights',
    ...       ['Assign', 'AnnAssign', 'AugAssign', 'NamedExpr', 'For', 'While'])
    True
    """
    "*** 在此处填写你的代码 ***"

    if(num < 10):
        return int(num == 8)
    else:
        return int(num % 10 == 8) + num_eights(num // 10)


def digit_distance(num: int) -> int:
    """计算 num 的数位距离。

    >>> digit_distance(3)
    0
    >>> digit_distance(777) # 0 + 0
    0
    >>> digit_distance(314) # 2 + 3
    5
    >>> digit_distance(31415926535) # 2 + 3 + 3 + 4 + ... + 2
    32
    >>> digit_distance(3464660003)  # 1 + 2 + 2 + 2 + ... + 3
    16
    >>> from construct_check import check
    >>> # 禁止使用所有循环
    >>> check(SOURCE_FILE, 'digit_distance',
    ...       ['For', 'While'])
    True
    """
    "*** 在此处填写你的代码 ***"
    if(num < 10):
        return 0
    else:
        return abs(num % 10 - num // 10 % 10) + digit_distance(num // 10)


def interleaved_sum(num: int, f_odd, f_even) -> int:
    """计算 f_odd(1) + f_even(2) + f_odd(3) + ...，一直累加到 num。

    >>> identity = lambda x: x
    >>> square = lambda x: x * x
    >>> triple = lambda x: x * 3
    >>> interleaved_sum(5, identity, square) # 1   + 2*2 + 3   + 4*4 + 5
    29
    >>> interleaved_sum(5, square, identity) # 1*1 + 2   + 3*3 + 4   + 5*5
    41
    >>> interleaved_sum(4, triple, square)   # 1*3 + 2*2 + 3*3 + 4*4
    32
    >>> interleaved_sum(4, square, triple)   # 1*1 + 2*3 + 3*3 + 4*3
    28
    >>> from construct_check import check
    >>> check(SOURCE_FILE, 'interleaved_sum', ['While', 'For', 'Mod']) # 禁止使用循环和 %
    True
    >>> check(SOURCE_FILE, 'interleaved_sum', ['BitAnd', 'BitOr', 'BitXor']) # 禁止使用位运算符；如果你不了解它们，也不用担心
    True
    """
    "*** 在此处填写你的代码 ***"

    """计算 f_odd(1) + f_even(2) + f_odd(3) + ...，一直累加到 num。"""

    def add_odd(i: int) -> int:
        if i > num:
            return 0
        return f_odd(i) + add_even(i + 1)

    def add_even(i: int) -> int:
        if i > num:
            return 0
        return f_even(i) + add_odd(i + 1)

    return add_odd(1)
    


def next_smaller_dollar(bill: int):
    """按顺序返回下一个面额更小的纸币。"""
    if bill == 100:
        return 50
    if bill == 50:
        return 20
    if bill == 20:
        return 10
    elif bill == 10:
        return 5
    elif bill == 5:
        return 1

def count_dollars(sum_needed: int) -> int:
    """返回凑出指定金额的方式数量。

    >>> count_dollars(15)  # 15 张 1 美元；10 张 1 美元和 1 张 5 美元；……；1 张 5 美元和 1 张 10 美元
    6
    >>> count_dollars(10)  # 10 张 1 美元；5 张 1 美元和 1 张 5 美元；2 张 5 美元；1 张 10 美元
    4
    >>> count_dollars(20)  # 20 张 1 美元；15 张 1 美元和 1 张 5 美元；……；1 张 20 美元
    10
    >>> count_dollars(45)  # 凑出 45 美元有多少种方式？
    44
    >>> count_dollars(100) # 凑出 100 美元有多少种方式？
    344
    >>> count_dollars(200) # 凑出 200 美元有多少种方式？
    3274
    >>> from construct_check import check
    >>> # 禁止使用迭代
    >>> check(SOURCE_FILE, 'count_dollars', ['While', 'For'])
    True
    """ 
    "*** 在此处填写你的代码 ***"

    def count(remain, bill):
        if (remain == 0):
            return 1
        elif (remain < 0 or bill is None):
            return 0

        return (count(remain - bill, bill) + count(remain, next_smaller_dollar(bill)))

    return count(sum_needed, 100)




def shuffle(s: list) -> list:
    """交错排列 s 的前后两半，并返回排列后的列表。

    >>> shuffle(range(6))
    [0, 3, 1, 4, 2, 5]
    >>> letters = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h']
    >>> shuffle(letters)
    ['a', 'e', 'b', 'f', 'c', 'g', 'd', 'h']
    >>> shuffle(shuffle(letters))
    ['a', 'c', 'e', 'g', 'b', 'd', 'f', 'h']
    >>> letters  # 不应修改原列表
    ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h']
    """
    assert len(s) % 2 == 0, '序列长度必须为偶数'
    "*** 在此处填写你的代码 ***"

    n = len(s) // 2

    ans: list = []
    for i in range(1, n + 1):
        ans += [s[i - 1]]
        ans += [s[i - 1 + n]]

    return ans

def deep_map(f, s: list) -> None:
    """在嵌套列表 s 中，将所有非列表元素 x 替换为 f(x)。

    >>> six = [1, 2, [3, [4], 5], 6]
    >>> deep_map(lambda x: x * x, six)
    >>> six
    [1, 4, [9, [16], 25], 36]
    >>> # 检查你没有创建新列表
    >>> s = [3, [1, [4, [1]]]]
    >>> s1 = s[1]
    >>> s2 = s1[1]
    >>> s3 = s2[1]
    >>> deep_map(lambda x: x + 1, s)
    >>> s
    [4, [2, [5, [2]]]]
    >>> s1 is s[1]
    True
    >>> s2 is s1[1]
    True
    >>> s3 is s2[1]
    True
    """
    "*** 在此处填写你的代码 ***"
    n = len(s)
    for i in range(n):
        if(type(s[i]) == list):
            deep_map(f, s[i])
        else:
            s[i] = f(s[i])



def next_larger_dollar(bill: int):
    """按顺序返回下一个面额更大的纸币。"""
    if bill == 1:
        return 5
    elif bill == 5:
        return 10
    elif bill == 10:
        return 20
    elif bill == 20:
        return 50
    elif bill == 50:
        return 100

def count_dollars_upward(sum_needed: int) -> int:
    """返回使用纸币凑出指定金额的方式数量。

    >>> count_dollars_upward(15)  # 15 张 1 美元；10 张 1 美元和 1 张 5 美元；……；1 张 5 美元和 1 张 10 美元
    6
    >>> count_dollars_upward(10)  # 10 张 1 美元；5 张 1 美元和 1 张 5 美元；2 张 5 美元；1 张 10 美元
    4
    >>> count_dollars_upward(20)  # 20 张 1 美元；15 张 1 美元和 1 张 5 美元；……；1 张 20 美元
    10
    >>> count_dollars_upward(45)  # 凑出 45 美元有多少种方式？
    44
    >>> count_dollars_upward(100) # 凑出 100 美元有多少种方式？
    344
    >>> count_dollars_upward(200) # 凑出 200 美元有多少种方式？
    3274
    >>> from construct_check import check
    >>> # 禁止使用迭代
    >>> check(SOURCE_FILE, 'count_dollars_upward', ['While', 'For'])
    True
    """
    "*** 在此处填写你的代码 ***"
    
    def count(remain, bill):
        if (remain == sum_needed):
            return 1
        elif (remain > sum_needed or bill is None):
            return 0

        return (count(remain + bill, bill) + count(remain, next_larger_dollar(bill)))

    return count(0, 1)
