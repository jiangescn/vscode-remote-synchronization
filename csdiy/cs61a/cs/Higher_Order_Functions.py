def identity(k):
    return k

def cube(k):
    return pow(k, 3)

def summation(n, term):
    """
    >>> summation(5, cube)
    225
    """
    sum = 0
    k = 1
    while k <= n:
        sum += term(k)
        k += 1
    return sum

def sum_nat(n):
    """
    >>> sum_nat(5)
    15
    """
    return summation(n, identity)

def sum_cub(n):
    """
    >>> sum_cub(5)
    225
    """
    return summation(n, cube)

print(sum_cub(10), end = '\n')
# print(f"\040")
# print(f"\040")
# print(f"\040")
print(sum_cub(5))
