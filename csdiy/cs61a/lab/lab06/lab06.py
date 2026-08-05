from __future__ import annotations


class Transaction:
    def __init__(self, id: int, before: int, after: int):
        self.id = id
        self.before = before
        self.after = after

    def changed(self) -> bool:
        """返回这笔交易是否使余额发生变化。"""
        "*** 在此处编写代码 ***"
        return self.before != self.after


    def report(self) -> str:
        """返回描述这笔交易的字符串。

        >>> Transaction(3, 20, 10).report()
        '3: decreased 20->10'
        >>> Transaction(4, 20, 50).report()
        '4: increased 20->50'
        >>> Transaction(5, 50, 50).report() 
        '5: no change'
        """
        msg: str = 'no change'
        if self.changed():
            "*** 在此处编写代码 ***"
            if(self.after > self.before):
                msg = f'increased {self.before}->{self.after}'
            else:
                msg = f'decreased {self.before}->{self.after}'
        return str(self.id) + ': ' + msg

class BankAccount:
    """一个能够记录交易历史的银行账户。

    >>> a = BankAccount('Eric')
    >>> a.deposit(100)    # a 的第 0 笔交易
    100
    >>> b = BankAccount('Erica')
    >>> a.withdraw(30)    # a 的第 1 笔交易
    70
    >>> a.deposit(10)     # a 的第 2 笔交易
    80
    >>> b.deposit(50)     # b 的第 0 笔交易
    50
    >>> b.withdraw(10)    # b 的第 1 笔交易
    40
    >>> a.withdraw(100)   # a 的第 3 笔交易
    'Insufficient funds'
    >>> len(a.transactions)
    4
    >>> len([t for t in a.transactions if t.changed()])
    3
    >>> for t in a.transactions:
    ...     print(t.report())
    0: increased 0->100
    1: decreased 100->70
    2: increased 70->80
    3: no change
    >>> b.withdraw(100)   # b 的第 2 笔交易
    'Insufficient funds'
    >>> b.withdraw(30)    # b 的第 3 笔交易
    10
    >>> for t in b.transactions:
    ...     print(t.report())
    0: increased 0->50
    1: decreased 50->40
    2: no change
    3: decreased 40->10
    """

    # *** 你需要修改这个类中的多个位置 ***

    def __init__(self, account_holder: str):
        self.balance: int = 0
        self.holder = account_holder
        self.transactions  = []

    def deposit(self, amount: int) -> int:
        """将账户余额增加 amount，把这笔存款加入交易历史，并返回新余额。
        """
        before = self.balance
        self.balance = self.balance + amount
        transaction = Transaction(len(self.transactions), before, self.balance)
        self.transactions.append(transaction)

        return self.balance

    def withdraw(self, amount: int) -> int | str:
        """将账户余额减少 amount，把这笔取款加入交易历史，并返回新余额。
        """
        before = self.balance
        if amount > self.balance:
            transaction = Transaction(len(self.transactions), before, self.balance)
            self.transactions.append(transaction)
            return 'Insufficient funds'
        self.balance = self.balance - amount
        transaction = Transaction(len(self.transactions), before, self.balance)
        self.transactions.append(transaction)
        return self.balance


class Email:
    """一封电子邮件具有以下实例属性：

        msg (str)：邮件内容
        sender (Client)：发送邮件的客户端
        recipient_name (str)：收件人的名称（另一个客户端）
    """
    def __init__(self, msg: str, sender, recipient_name: str):
        self.msg = msg
        self.sender = sender
        self.recipient_name = recipient_name

class Server:
    """每个 Server 都有一个名为 clients 的实例属性，
    它是从客户端名称到客户端对象的字典。

    >>> s = Server()
    >>> # 仅供测试使用的模拟 Client 类实现
    >>> class Client:
    ...     def __init__(self, server, name):
    ...         self.inbox = []
    ...         self.server = server
    ...         self.name = name
    >>> a = Client(s, 'Alice')
    >>> b = Client(s, 'Bob')
    >>> s.register_client(a) 
    >>> s.register_client(b)
    >>> len(s.clients)  # 我们已经注册了 2 个客户端
    2
    >>> all([type(c) == str for c in s.clients.keys()])  # self.clients 中的键应当是字符串
    True
    >>> all([type(c) == Client for c in s.clients.values()])  # self.clients 中的值应当是 Client 实例
    True
    >>> new_a = Client(s, 'Alice')  # 创建一个与现有客户端同名的新客户端
    >>> s.register_client(new_a)
    >>> len(s.clients)  # 字典中的键必须唯一
    2
    >>> s.clients['Alice'] is new_a  # 键 'Alice' 对应的值现在应更新为新客户端 new_a
    True
    >>> e = Email("I love 61A", b, 'Alice')
    >>> s.send(e)
    >>> len(new_a.inbox)  # 已经向新的 Alice 发送了一封邮件
    1
    >>> type(new_a.inbox[0]) == Email  # Client 的收件箱是由 Email 实例组成的列表
    True
    """
    def __init__(self):
        self.clients = {}

    def send(self, email: Email):
        """把邮件追加到收件人的收件箱中。
            email 是 Email 类的实例。
        """
        self.clients[email.recipient_name].inbox.append(email)

    def register_client(self, client):
        """把客户端加入 clients 映射（即从客户端名称到客户端实例的字典）。
            client 是 Client 类的实例。
        """
        self.clients[client.name] = client

class Client:
    """客户端拥有服务器、名称（str）和收件箱（list）。

    >>> s = Server()
    >>> a = Client(s, 'Alice')
    >>> b = Client(s, 'Bob')
    >>> a.compose('Hello, World!', 'Bob')
    >>> b.inbox[0].msg
    'Hello, World!'
    >>> a.compose('CS 61A Rocks!', 'Bob')
    >>> len(b.inbox)
    2
    >>> b.inbox[1].msg
    'CS 61A Rocks!'
    >>> b.inbox[1].sender.name
    'Alice'
    """
    def __init__(self, server: Server, name: str):
        self.inbox: list = []
        self.server = server
        self.name = name
        server.register_client(self)

    def compose(self, message: str, recipient_name: str):
        """向收件人发送一封包含指定消息的电子邮件。"""
        email = Email(message, self, recipient_name)
        self.server.send(email)


class Mint:
    """铸币厂通过在硬币上压印年份来制造硬币。

    update 方法会把铸币厂的年份印记设为 Mint.present_year。

    >>> mint = Mint()
    >>> mint.year
    2025
    >>> dime = mint.create(Dime)
    >>> dime.year
    2025
    >>> Mint.present_year = 2105  # 时间流逝
    >>> nickel = mint.create(Nickel)
    >>> nickel.year     # 这个铸币厂尚未更新它的年份印记
    2025
    >>> nickel.worth()  # 5 美分 +（80 年 - 50 年）
    35
    >>> mint.update()   # 将这个铸币厂的年份更新为 2105
    >>> Mint.present_year = 2180     # 更多时间过去了
    >>> mint.create(Dime).worth()    # 10 美分 +（75 年 - 50 年）
    35
    >>> Mint().create(Dime).worth()  # 新建的铸币厂使用当前年份
    10
    >>> dime.worth()     # 10 美分 +（155 年 - 50 年）
    115
    >>> Dime.cents = 20  # 提高所有十美分硬币的面值！
    >>> dime.worth()     # 20 美分 +（155 年 - 50 年）
    125
    """
    present_year = 2025

    def __init__(self):
        self.update()

    def create(self, coin):
        "*** 在此处编写代码 ***"
        return coin(self.year)

    def update(self) -> None:
        "*** 在此处编写代码 ***"
        self.year = self.present_year

class Coin:
    cents:int # 该属性由子类提供，而不是由 Coin 本身提供

    def __init__(self, year: int):
        self.year = year

    def worth(self) -> int:
        "*** 在此处编写代码 ***"
        age: int = Mint.present_year - self.year
        value: int = max(0, age - 50)
        return self.cents + value

class Nickel(Coin):
    cents = 5

class Dime(Coin):
    cents = 10


class VirFib():
    """一个 Virahanka Fibonacci 数。

    >>> start = VirFib()
    >>> start
    VirFib object, value 0
    >>> start.next()
    VirFib object, value 1
    >>> start.next().next()
    VirFib object, value 1
    >>> start.next().next().next()
    VirFib object, value 2
    >>> start.next().next().next().next()
    VirFib object, value 3
    >>> start.next().next().next().next().next()
    VirFib object, value 5
    >>> start.next().next().next().next().next().next()
    VirFib object, value 8
    >>> start.next().next().next().next().next().next() # 确保 start 没有被修改
    VirFib object, value 8
    """
    previous: VirFib

    def __init__(self, value: int = 0):
        self.value = value

    def next(self):
        "*** 在此处编写代码 ***"
        if(self.value == 0):
            result = VirFib(1)
        else:
            result = VirFib(self.value + self.previous.value)

        result.previous = self
        return result

    def __repr__(self) -> str:
        return "VirFib object, value " + str(self.value)

