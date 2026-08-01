# Lab02 实用工具

UPPERCASE_SHIFT = 65
LOWERCASE_SHIFT = 97
ALPHA_SHIFT = 26

def letter_to_num(letter):
    """将所有字母转换为 0–51 的数字，其中小写字母映射到 0–25，
    大写字母映射到 26–51。
    >>> letter_to_num('a')
    0
    >>> letter_to_num('z')
    25
    >>> letter_to_num('A')
    26
    >>> letter_to_num('Z')
    51
    """
    if letter.isupper():
        return ord(letter)-UPPERCASE_SHIFT + ALPHA_SHIFT
    return ord(letter)-LOWERCASE_SHIFT

def num_to_letter(num):
    """将 0–51 的数字转换为字母。
    >>> num_to_letter(0)
    'a'
    >>> num_to_letter(25)
    'z'
    >>> num_to_letter(26)
    'A'
    >>> num_to_letter(51)
    'Z'
    """
    try:
        num = int(num)
    except ValueError:
        return ' '
    num = num % 52
    if num > 25:
        return chr(num - ALPHA_SHIFT + UPPERCASE_SHIFT)
    return chr(num + LOWERCASE_SHIFT)

def mirror_letter(letter):
    """返回字母表另一端对称位置上的字母。

    >>> mirror_letter('a')
    'z'
    >>> mirror_letter('z')
    'a'
    >>> mirror_letter('B')
    'Y'
    >>> mirror_letter('C')
    'X'
    """
    if letter.isupper():
        return chr(155 - ord(letter))
    return chr(219 - ord(letter))


def looper(f, delimiter=''):
    """返回一个将函数 f 应用于可迭代对象每个元素的函数。"""
    return lambda iterable: delimiter.join([str(f(i)) for i in iterable])



def composite_identity(f, g):
    """
    返回一个只有一个参数 x 的函数。如果 f(g(x)) 等于 g(f(x))，
    该函数返回 True。可以假设 g(x) 的结果是 f 的有效输入，
    反之亦然。

    >>> add_one = lambda x: x + 1        # 将 x 加 1
    >>> square = lambda x: x**2          # 对 x 求平方（返回 x^2）
    >>> b1 = composite_identity(square, add_one)
    >>> b1(0)                            # (0 + 1) ** 2 == 0 ** 2 + 1
    True
    >>> b1(4)                            # (4 + 1) ** 2 != 4 ** 2 + 1
    False
    """
    "*** 在此处编写代码 ***"
    def func(x):
        return g(f(x)) == f(g(x))

    return func
    


def sum_digits(y):
    """返回非负整数 y 的各位数字之和。"""
    total = 0
    while y > 0:
        total, y = total + y % 10, y // 10
    return total

def is_prime(n):
    """返回正整数 n 是否为质数。"""
    if n == 1:
        return False
    k = 2
    while k < n:
        if n % k == 0:
            return False
        k += 1
    return True

def count_cond(condition):
    """返回一个只有一个参数 N 的函数，用于统计 1 到 n 中所有
    满足双参数谓词函数 Condition 的数。其中，condition 的第一个
    参数是 n，第二个参数是 1 到 n 中的数。

    >>> count_fives = count_cond(lambda n, i: sum_digits(n * i) == 5)
    >>> count_fives(10)   # 50 (10 * 5)
    1
    >>> count_fives(50)   # 50 (50 * 1), 500 (50 * 10), 1400 (50 * 28), 2300 (50 * 46)
    4

    >>> is_i_prime = lambda n, i: is_prime(i) # 需要向 count_cond 传入双参数函数
    >>> count_primes = count_cond(is_i_prime)
    >>> count_primes(2)    # 2
    1
    >>> count_primes(3)    # 2, 3
    2
    >>> count_primes(4)    # 2, 3
    2
    >>> count_primes(5)    # 2, 3, 5
    3
    >>> count_primes(20)   # 2, 3, 5, 7, 11, 13, 17, 19
    8
    """
    "*** 在此处编写代码 ***"

    def func(n):
        count = 0
        for i in range(1, n + 1):
            if(condition(n, i)):
                count += 1
        return count
    return func




from operator import add, sub

def caesar_generator(num, op):
    """返回一个单参数的凯撒密码函数。该函数应使用运算 'op'
    （add 或 sub）将字母“旋转”整数 'num' 个位置。

    可以使用已提供的 `letter_to_num` 和 `num_to_letter` 函数；
    它们会将所有小写字母 a–z 映射到 0–25，并将所有大写字母
    A–Z 映射到 26–51。

    >>> letter_to_num('a')
    0
    >>> letter_to_num('c')
    2
    >>> num_to_letter(3)
    'd'

    >>> caesar2 = caesar_generator(2, add)
    >>> caesar2('a')
    'c'
    >>> brutus3 = caesar_generator(3, sub)
    >>> brutus3('d')
    'a'
    """
    "*** 在此处编写代码 ***"
    return lambda letter: num_to_letter(op(letter_to_num(letter), num) % 26)


def is_palindrome(n):
    """
    填写空格 '_____' 以检查一个数是否为回文数。

    >>> is_palindrome(12321)
    True
    >>> is_palindrome(42)
    False
    >>> is_palindrome(2015)
    False
    >>> is_palindrome(55)
    True
    """
    x, y = n, 0
    f = lambda: y * 10 + x % 10
    while x > 0:
        x, y = x // 10, f()
    return y == n
