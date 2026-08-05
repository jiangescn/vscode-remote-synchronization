from __future__ import annotations


class VendingMachine:
    """一台以指定价格销售某种商品的自动售货机。

    >>> v = VendingMachine('candy', 10)
    >>> v.vend()
    'Nothing left to vend. Please restock.'
    >>> v.add_funds(15)
    'Nothing left to vend. Please restock. Here is your $15.'
    >>> v.restock(2)
    'Current candy stock: 2'
    >>> v.vend()
    'Please add $10 more funds.'
    >>> v.add_funds(7)
    'Current balance: $7'
    >>> v.vend()
    'Please add $3 more funds.'
    >>> v.add_funds(5)
    'Current balance: $12'
    >>> v.vend()
    'Here is your candy and $2 change.'
    >>> v.add_funds(10)
    'Current balance: $10'
    >>> v.vend()
    'Here is your candy.'
    >>> v.add_funds(15)
    'Nothing left to vend. Please restock. Here is your $15.'

    >>> w = VendingMachine('soda', 2)
    >>> w.restock(3)
    'Current soda stock: 3'
    >>> w.restock(3)
    'Current soda stock: 6'
    >>> w.add_funds(2)
    'Current balance: $2'
    >>> w.vend()
    'Here is your soda.'
    """
    def __init__(self, product: str, price: int):
        """设置商品、价格以及其他实例属性。"""
        "*** 在此处填写你的代码 ***"
        self.product = product
        self.price = price
        self.restone = 0
        self.balance = 0

    def restock(self, n: int) -> str:
        """把库存增加 n，并返回说明最新库存数量的消息。

        例如：Current candy stock: 3
        """
        "*** 在此处填写你的代码 ***"
        self.restone += n
        return f"Current {self.product} stock: {self.restone}"

    def add_funds(self, n: int) -> str:
        """如果机器缺货，返回提示用户补货的消息（并退还其投入的 n 美元）。

        例如：Nothing left to vend. Please restock. Here is your $4.

        否则，把 n 加入余额，并返回说明最新余额的消息。

        例如：Current balance: $4
        """
        "*** 在此处填写你的代码 ***"
        if self.restone == 0:
            return f"Nothing left to vend. Please restock. Here is your ${n}."
        
        self.balance += n
        return f"Current balance: ${self.balance}"

    def vend(self) -> str:
        """如果库存和投入金额充足，就售出商品并返回相应消息，同时更新库存和余额。

        例如：Here is your candy and $2 change.

        否则，返回说明如何解决问题的消息。

        例如：Nothing left to vend. Please restock.
              Please add $3 more funds.
        """
        "*** 在此处填写你的代码 ***"
        if(self.restone == 0):
            return "Nothing left to vend. Please restock."

        if(self.balance < self.price):
            return f"Please add ${self.price - self.balance} more funds."

        self.restone -= 1
        change = self.balance - self.price
        self.balance = 0

        if(change > 0):
            return f"Here is your {self.product} and ${change} change."
        else:
            return f"Here is your {self.product}."




def cumulative_mul(t: Tree) -> None:
    """改变 t，使每个节点的标签变为自身标签与其对应子树中所有标签的乘积。

    >>> t = Tree(1, [Tree(3, [Tree(5)]), Tree(7)])
    >>> cumulative_mul(t)
    >>> t
    Tree(105, [Tree(15, [Tree(5)]), Tree(7)])
    >>> otherTree = Tree(2, [Tree(1, [Tree(3), Tree(4), Tree(5)]), Tree(6, [Tree(7)])])
    >>> cumulative_mul(otherTree)
    >>> otherTree
    Tree(5040, [Tree(60, [Tree(3), Tree(4), Tree(5)]), Tree(42, [Tree(7)])])
    """
    "*** 在此处填写你的代码 ***"
    for i in t.branches:
        cumulative_mul(i)
        t.label *= i.label
    



def prune_small(t: Tree, n: int) -> None:
    """就地修剪树，使每个节点只保留标签最小的 n 个分支。

    >>> t1 = Tree(6)
    >>> prune_small(t1, 2)
    >>> t1
    Tree(6)
    >>> t2 = Tree(6, [Tree(3), Tree(4)])
    >>> prune_small(t2, 1)
    >>> t2
    Tree(6, [Tree(3)])
    >>> t3 = Tree(6, [Tree(1), Tree(3, [Tree(1), Tree(2), Tree(3)]), Tree(5, [Tree(3), Tree(4)])])
    >>> prune_small(t3, 2)
    >>> t3
    Tree(6, [Tree(1), Tree(3, [Tree(1), Tree(2)])])
    """
    while len(t.branches) > n:
        largest = max(t.branches, key=lambda b:b.label)
        t.branches.remove(largest)
    for b in t.branches:
        prune_small(b, n)


class Pet:

    def __init__(self, name: str, owner: str) -> None:
        self.name = name
        self.owner = owner

    def talk(self) -> None:
        print(self.name)

class Cat(Pet):
    """
    >>> my_cat = Cat("Furball", "Me", lives=2)
    >>> my_cat.talk()
    Meow!
    >>> my_cat.name
    'Furball'
    >>> my_cat.lose_life()
    >>> my_cat.is_alive
    True
    >>> my_cat.eat("poison")
    Meow!
    Furball ate a poison!
    >>> my_cat.is_alive
    False
    >>> my_cat.lose_life()
    'Cat is dead x_x'
    """
    def __init__(self, name: str, owner: str, lives: int = 9) -> None:
        assert type(lives) == int and  lives > 0
        "*** 在此处填写你的代码 ***"
        self.name = name
        self.owner = owner
        self.lives = lives
        self.is_alive = True

    def talk(self) -> None:
        """猫在被要求说话时会说“Meow!”。"""
        "*** 在此处填写你的代码 ***"
        print("Meow!")

    def lose_life(self) -> str | None:
        """猫只有在至少还有一条命时才能失去一条命。生命数变为零时，变量 is_alive 会变为 False。
        """
        "*** 在此处填写你的代码 ***"
        if(not self.is_alive):
            return 'Cat is dead x_x'
        else:
            self.lives -= 1
            if(self.lives == 0):
                self.is_alive = False


    def eat(self, thing: str) -> None:
        self.talk()
        print(f"{self.name} ate a {thing}!")
        if thing == "poison":
            self.is_alive = False


class Tree:
    """一棵树具有一个标签和一个分支列表。

    >>> t = Tree(3, [Tree(2, [Tree(5)]), Tree(4)])
    >>> t.label
    3
    >>> t.branches[0].label
    2
    >>> t.branches[1].is_leaf()
    True
    """
    def __init__(self, label, branches=[]):
        self.label = label
        for branch in branches:
            assert isinstance(branch, Tree)
        self.branches = list(branches)

    def is_leaf(self):
        return not self.branches

    def __repr__(self):
        if self.branches:
            branch_str = ', ' + repr(self.branches)
        else:
            branch_str = ''
        return 'Tree({0}{1})'.format(repr(self.label), branch_str)

    def __str__(self):
        return '\n'.join(self.indented())

    def indented(self):
        lines = []
        for b in self.branches:
            for line in b.indented():
                lines.append('  ' + line)
        return [str(self.label)] + lines

