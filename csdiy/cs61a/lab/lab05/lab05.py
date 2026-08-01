from __future__ import annotations # 使类型注解可以正常工作
from typing import Iterator  # “t: Iterator[int]”表示 t 是一个产生整数的迭代器


SOURCE_FILE = __file__


def insert_items(s: list[int], before: int, after: int) -> list[int]:
    """在 s 中每次出现 before 后插入 after，然后返回 s。

    >>> test_s = [1, 5, 8, 5, 2, 3]
    >>> new_s = insert_items(test_s, 5, 7)
    >>> new_s
    [1, 5, 7, 8, 5, 7, 2, 3]
    >>> test_s
    [1, 5, 7, 8, 5, 7, 2, 3]
    >>> new_s is test_s
    True
    >>> double_s = [1, 2, 1, 2, 3, 3]
    >>> double_s = insert_items(double_s, 3, 4)
    >>> double_s
    [1, 2, 1, 2, 3, 4, 3, 4]
    >>> large_s = [1, 4, 8]
    >>> large_s2 = insert_items(large_s, 4, 4)
    >>> large_s2
    [1, 4, 4, 8]
    >>> large_s3 = insert_items(large_s2, 4, 6)
    >>> large_s3
    [1, 4, 6, 4, 6, 8]
    >>> large_s3 is large_s
    True
    """
    "*** 在此处填写你的代码 ***"
    i = 0
    while (i < len(s)):
        if(s[i] == before):
            s.insert(i + 1, after)
            i += 2
        else:
            i += 1
    return s





def group_by(s: list[int], fn) -> dict[int, list[int]]:
    """返回一个由若干列表组成的字典，这些列表合起来包含 s 的所有元素。
    每个列表对应的键，是将 fn 应用于该列表中任意元素时所返回的值。

    >>> group_by([12, 23, 14, 45], lambda p: p // 10)
    {1: [12, 14], 2: [23], 4: [45]}
    >>> group_by(range(-3, 4), lambda x: x * x)
    {9: [-3, 3], 4: [-2, 2], 1: [-1, 1], 0: [0]}
    """
    grouped = {}
    for i in s:
        key = fn(i)
        if key in grouped:
            grouped[key].append(i)
        else:
            grouped[key] = [i]
    return grouped



def count_occurrences(t: Iterator[int], n: int, x: int) -> int:
    """返回迭代器 t 的前 n 个元素中等于 x 的元素数量。

    >>> s = iter([10, 9, 10, 9, 9, 10, 8, 8, 8, 7])
    >>> count_occurrences(s, 10, 9)
    3
    >>> t = iter([10, 9, 10, 9, 9, 10, 8, 8, 8, 7])
    >>> count_occurrences(t, 3, 10)
    2
    >>> u = iter([3, 2, 2, 2, 1, 2, 1, 4, 4, 5, 5, 5])
    >>> count_occurrences(u, 1, 3)  # 只遍历 3
    1
    >>> count_occurrences(u, 3, 2)  # 只遍历 2、2、2
    3
    >>> list(u)                     # 确保迭代器恰好前进了正确的距离
    [1, 2, 1, 4, 4, 5, 5, 5]
    >>> v = iter([4, 1, 6, 6, 7, 7, 6, 6, 2, 2, 2, 5])
    >>> count_occurrences(v, 6, 6)
    2
    """
    "*** 在此处填写你的代码 ***"
    ans = 0
    while(n != 0):
        n -= 1
        if(next(t) == x):
            ans += 1
    return ans



def perms(seq):
    """生成给定序列的所有排列。每个排列都是一个列表，其中包含 SEQ 的
    所有元素，但顺序各不相同。生成这些排列时可以采用任意顺序。

    >>> p = perms([100])
    >>> type(p)
    <class 'generator'>
    >>> next(p)
    [100]
    >>> try: # 如果调用 next 会导致错误，则打印“No more permutations!”
    ...     next(p)
    ... except StopIteration:
    ...     print('No more permutations!')
    No more permutations!
    >>> sorted(perms([1, 2, 3])) # 返回包含生成器中所有元素的已排序列表
    [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]]
    >>> sorted(perms((10, 20, 30)))
    [[10, 20, 30], [10, 30, 20], [20, 10, 30], [20, 30, 10], [30, 10, 20], [30, 20, 10]]
    >>> sorted(perms("ab"))
    [['a', 'b'], ['b', 'a']]
    """
    "*** 在此处填写你的代码 ***"
    if len(seq) == 1:
        yield [seq[0]]
    else:
        first = seq[0]
        for i in perms(seq[1:]):
            for j in range(len(i) + 1):
                yield i[:j] + [first] + i[j:]




def repeated(t: Iterator[int], k: int) -> int:
    """返回迭代器 t 中第一个连续出现 k 次的值，
    并使对 t 调用 next 的次数尽可能少。

    >>> s = iter([10, 9, 10, 9, 9, 10, 8, 8, 8, 7])
    >>> repeated(s, 2)
    9
    >>> t = iter([10, 9, 10, 9, 9, 10, 8, 8, 8, 7])
    >>> repeated(t, 3)
    8
    >>> u = iter([3, 2, 2, 2, 1, 2, 1, 4, 4, 5, 5, 5])
    >>> repeated(u, 3)
    2
    >>> repeated(u, 3)
    5
    >>> v = iter([4, 1, 6, 6, 7, 7, 8, 8, 2, 2, 2, 5])
    >>> repeated(v, 3)
    2
    """
    assert k > 1
    "*** 在此处填写你的代码 ***"

    count = 1
    last = next(t)

    while(count < k):
        cur = next(t)
        if(cur == last):
            count += 1
        else:
            count = 1
            last = cur

    return last

