"""打字测试的实现"""

from utils import (
    lower,
    split,
    remove_punctuation,
    lines_from_file,
    count,
    deep_convert_to_tuple,
)
from ucb import main, interact, trace
from datetime import datetime
import random


###########
# 阶段 1  #
###########


def pick(paragraphs: list[str], select, k: int) -> str:
    """返回 PARAGRAPHS 中第 K 个使 SELECT 函数返回 True 的段落。
    如果符合条件的段落不足 K 个，则返回空字符串。

    参数：
        paragraphs：表示各个段落的字符串列表
        select：对符合条件的段落返回 True 的函数
        k：表示要返回第几个段落的整数

    >>> ps = ['hi', 'how are you', 'fine']
    >>> s = lambda p: len(p) <= 4
    >>> pick(ps, s, 0)
    'hi'
    >>> pick(ps, s, 1)
    'fine'
    >>> pick(ps, s, 2)
    ''
    """
    # BEGIN PROBLEM 1
    count = 0

    for i in paragraphs:
        if(select(i)):
            if(count == k):
                return i
            count += 1
    return ''
    "*** 在此处填写你的代码 ***"
    # END PROBLEM 1


def about(keywords: list[str]):
    """返回一个函数。该函数接收一个段落，并判断段落中是否包含
    keywords 中的某个单词。

    参数：
        keywords：关键词列表

    >>> about_dogs = about(['dog', 'dogs', 'pup', 'puppy'])
    >>> pick(['Cute Dog!', 'That is a cat.', 'Nice pup!'], about_dogs, 0)
    'Cute Dog!'
    >>> pick(['Cute Dog!', 'That is a cat.', 'Nice pup.'], about_dogs, 1)
    'Nice pup.'
    """
    assert all([lower(x) == x for x in keywords]), "关键词应全部为小写。"

    # BEGIN PROBLEM 2
    "*** 在此处填写你的代码 ***"
    def incld(sentense):
        sentense = lower(sentense)
        sentense = remove_punctuation(sentense)
        sentense = split(sentense)
        for i in range(len(keywords)):
            if (keywords[i] in sentense):
                return True
        return False
    return incld        
    # END PROBLEM 2


def accuracy(entered: str, source: str) -> float:
    """将 ENTERED 与 SOURCE 中对应的单词进行比较，返回输入正确率
    （正确输入的单词所占百分比）。

    参数：
        entered：可能包含拼写错误的输入字符串
        source：不含错误的标准字符串

    >>> accuracy('Cute Dog!', 'Cute Dog.')
    50.0
    >>> accuracy('A Cute Dog!', 'Cute Dog.')
    0.0
    >>> accuracy('cute Dog.', 'Cute Dog.')
    50.0
    >>> accuracy('Cute Dog. I say!', 'Cute Dog.')
    50.0
    >>> accuracy('Cute', 'Cute Dog.')
    100.0
    >>> accuracy('', 'Cute Dog.')
    0.0
    >>> accuracy('', '')
    100.0
    """
    entered_words = split(entered)
    source_words = split(source)
    # BEGIN PROBLEM 3
    "*** 在此处填写你的代码 ***"
    n = len(source_words)
    m = len(entered_words)

    if(n == 0 and m == 0):
        return 100.0
    if(n == 0 and m != 0):
        return 0.0
    if(n != 0 and m == 0):
        return 0.0
    
    right = 0
    mn = min(m, n)
    for i in range(mn):
        if(entered_words[i] == source_words[i]):
            right += 1

    return 100 * right / m
    # END PROBLEM 3


def wpm(entered: str, elapsed: int) -> float:
    """返回字符串 ENTERED 的每分钟字数（WPM）。

    参数：
        entered：输入的字符串
        elapsed：经过的秒数

    >>> wpm('hello friend hello buddy hello', 15)
    24.0
    >>> wpm('0123456789',60)
    2.0
    """
    assert elapsed > 0, "经过的时间必须为正数"
    # BEGIN PROBLEM 4
    "*** 在此处填写你的代码 ***"
    n = len(entered)
    return float(n / 5 * 60 / elapsed)
    # END PROBLEM 4


##################
# 阶段 4（加分） #
##################


def memo(f):
    """通用的记忆化装饰器。"""
    cache = {}

    def memoized(*args):
        immutable_args = deep_convert_to_tuple(args)  # 将 *args 转换为元组形式
        if immutable_args not in cache:
            result = f(*immutable_args)
            cache[immutable_args] = result
            return result
        return cache[immutable_args]

    return memoized


def memo_diff(diff_function):
    """记忆化函数。"""
    cache = {}

    def memoized(entered, source, limit):
        # BEGIN PROBLEM EC
        "*** 在此处填写你的代码 ***"
        # END PROBLEM EC

    return memoized


###########
# 阶段 2  #
###########


def autocorrect(entered_word: str, word_list: list[str], diff_function, limit: int) -> str:
    """根据 DIFF_FUNCTION 返回 WORD_LIST 中与 ENTERED_WORD 差异最小的元素。
    如果多个单词的最小差异相同，则返回 WORD_LIST 中位置最靠前的单词。
    如果最小差异大于 LIMIT，则返回 ENTERED_WORD。

    参数：
        entered_word：表示可能包含拼写错误的单词的字符串
        word_list：表示标准单词的字符串列表
        diff_function：量化两个单词之间差异的函数
        limit：一个数值

    >>> ten_diff = lambda w1, w2, limit: 10 # 始终返回 10
    >>> autocorrect("hwllo", ["butter", "hello", "potato"], ten_diff, 20)
    'butter'
    >>> first_diff = lambda w1, w2, limit: (1 if w1[0] != w2[0] else 0) # 检查首字母是否相同
    >>> autocorrect("tosting", ["testing", "asking", "fasting"], first_diff, 10)
    'testing'
    """
    # BEGIN PROBLEM 5
    "*** 在此处填写你的代码 ***"
    if entered_word in word_list:
        return entered_word

    diff = 0
    count = diff_function(entered_word, word_list[0], limit)
    for i in range(1, len(word_list)):
        if(diff_function(entered_word, word_list[i], limit) < count):
            diff = i
            count = diff_function(entered_word, word_list[i], limit)
    if(count <= limit):
        return word_list[diff]
    else:
        return entered_word
    # END PROBLEM 5


def furry_fixes(entered: str, source: str, limit: int) -> int:
    """供 autocorrect 使用的差异函数。它计算需要替换 ENTERED 中的多少个字母
    才能得到 SOURCE，再加上两者长度之差，并返回结果。

    参数：
        entered：起始单词
        source：表示目标单词的字符串
        limit：表示最多需要更改多少个字符的上限

    >>> big_limit = 10
    >>> furry_fixes("nice", "rice", big_limit)    # 替换：n -> r
    1
    >>> furry_fixes("range", "rungs", big_limit)  # 替换：a -> u，e -> s
    2
    >>> furry_fixes("pill", "pillage", big_limit) # 无需替换，长度相差 3
    3
    >>> furry_fixes("roses", "arose", big_limit)  # 替换：r -> a，o -> r，s -> o，e -> s，s -> e
    5
    >>> furry_fixes("rose", "hello", big_limit)   # 替换：r->h，o->e，s->l，e->l，长度相差 1
    5
    """
    # BEGIN PROBLEM 6
    if (limit < 0):
        return 1

    if not entered or not source:
        return abs(len(entered) - len(source))

    if entered[0] == source[0]:
        return furry_fixes(entered[1:], source[1:], limit)

    return 1 + furry_fixes(entered[1:], source[1:], limit - 1)
    assert False, '删除这一行'
    # END PROBLEM 6


def minimum_mewtations(entered: str, source: str, limit: int) -> int:
    """供 autocorrect 使用的差异函数，用于计算从 ENTERED 到 SOURCE 的编辑距离。
    此函数接收字符串 ENTERED、字符串 SOURCE 和数值 LIMIT。

    参数：
        entered：起始单词
        source：表示目标单词的字符串
        limit：编辑次数的上限

    >>> big_limit = 10
    >>> minimum_mewtations("cats", "scat", big_limit)       # cats -> scats -> scat
    2
    >>> minimum_mewtations("purng", "purring", big_limit)   # purng -> purrng -> purring
    2
    >>> minimum_mewtations("ckiteus", "kittens", big_limit) # ckiteus -> kiteus -> kitteus -> kittens
    3
    """
    # assert False, '删除这一行'
    if limit < 0: # 基本情况应写在这里；你可以根据需要添加更多基本情况
        # BEGIN
        "*** 在此处填写你的代码 ***"
        return limit + 1
        # END
    if entered == source:
        return 0

    if not entered or not source:
        return abs(len(entered) - len(source))


    # 递归情况应写在下面
    if entered[0] == source[0]: # 可以随意删除或添加其他情况
        # BEGIN
        return minimum_mewtations(entered[1:], source[1:], limit)
        # END
    else:
        add = 1 + minimum_mewtations(entered, source[1:], limit - 1)
        remove = 1 + minimum_mewtations(entered[1:], source, limit - 1)
        substitute = 1 + minimum_mewtations(entered[1:], source[1:], limit - 1)
        # BEGIN
        return min(add, remove, substitute)
        # END


# 忽略下面这一行
minimum_mewtations = count(minimum_mewtations) # type: ignore


def final_diff(entered: str, source: str, limit: int) -> int:
    """差异函数，接收字符串 ENTERED、字符串 SOURCE 和数值 LIMIT。
    如果你实现了此函数，程序将使用它。"""
    # assert False, "删除这一行以使用你的 final_diff 函数。"
    if limit < 0: # 基本情况应写在这里；你可以根据需要添加更多基本情况
        # BEGIN
        "*** 在此处填写你的代码 ***"
        return limit + 1
        # END
    if entered == source:
        return 0

    if not entered or not source:
        return abs(len(entered) - len(source))


    # 递归情况应写在下面
    if entered[0] == source[0]: # 可以随意删除或添加其他情况
        # BEGIN
        return minimum_mewtations(entered[1:], source[1:], limit)
        # END
    else:
        add = 1 + minimum_mewtations(entered, source[1:], limit - 1)
        remove = 1 + minimum_mewtations(entered[1:], source, limit - 1)
        substitute = 1 + minimum_mewtations(entered[1:], source[1:], limit - 1)
        # BEGIN
        return min(add, remove, substitute)
            # END


FINAL_DIFF_LIMIT = 5  # 将此处替换为你的限制值


###########
# 阶段 3  #
###########


def report_progress(entered: list[str], source: list[str], user_id: int, upload) -> float:
    """将你的用户编号和当前进度报告上传至多人服务器，
    并返回当前进度。

    参数：
        entered：目前已经输入的单词列表
        source：打字标准文本中的单词列表
        user_id：表示当前用户编号的数值
        upload：用于将进度上传至多人服务器的函数

    >>> print_progress = lambda d: print('ID:', d['id'], 'Progress:', d['progress'])
    >>> # 上面的函数以 ID: __, Progress: __ 的格式显示进度
    >>> print_progress({'id': 1, 'progress': 0.6})
    ID: 1 Progress: 0.6
    >>> entered = ['how', 'are', 'you']
    >>> source = ['how', 'are', 'you', 'doing', 'today']
    >>> report_progress(entered, source, 2, print_progress)
    ID: 2 Progress: 0.6
    0.6
    >>> report_progress(['how', 'aree'], source, 3, print_progress)
    ID: 3 Progress: 0.2
    0.2
    """
    # BEGIN PROBLEM 8
    "*** 在此处填写你的代码 ***"
    count = 0
    mn = min(len(entered), len(source))

    for i in range(mn):
        if(entered[i] == source[i]):
            count += 1
        else:
            break
    ans = count / len(source)
    upload({'id': user_id, 'progress': ans})
    return ans
    # END PROBLEM 8


def time_per_word(words: list[str], timestamps_per_player: list[list[int]]) -> dict:
    """返回字典 {'words': words, 'times': times}。其中，times 是一个列表的列表，
    记录每位玩家输入 words 中各个单词所花费的时间。

    参数：
        words：按照输入顺序排列的单词列表。
        timestamps_per_player：由时间戳列表组成的列表，其中先记录每位玩家
                               开始输入的时间，再依次记录其输完各个单词的时间。

    >>> p = [[75, 81, 84, 90, 92], [19, 29, 35, 36, 38]]
    >>> result = time_per_word(['collar', 'plush', 'blush', 'repute'], p)
    >>> result['words']
    ['collar', 'plush', 'blush', 'repute']
    >>> result['times']
    [[6, 3, 6, 2], [10, 6, 1, 2]]
    """
    ts_by_player = timestamps_per_player  # 使用较短的名称（便于书写）
    # BEGIN PROBLEM 9
    times = []  # 你可以删除这一行
    for i in range(len(timestamps_per_player)):
        pre = []
        for j in range (1, len(timestamps_per_player[i])):
                pre += [ts_by_player[i][j] - ts_by_player[i][j - 1]]
        times += [pre]
    # END PROBLEM 9
    return {'words': words, 'times': times}


def fastest_words(words_and_times: dict) -> list[list[str]]:
    """返回一个列表的列表，表示每位玩家输入速度最快的单词。
    如果出现并列，则认为索引较小的玩家输入该单词的速度最快。

    参数：
        words_and_times：字典 {'words': words, 'times': times}，其中 words 是
                         已输入的单词列表，times 是一个列表的列表，记录每位
                         玩家输入每个单词所花费的时间。

    >>> p0 = [5, 1, 3]
    >>> p1 = [4, 1, 6]
    >>> fastest_words({'words': ['Just', 'have', 'fun'], 'times': [p0, p1]})
    [['have', 'fun'], ['Just']]
    >>> p0  # 不应修改输入列表
    [5, 1, 3]
    >>> p1
    [4, 1, 6]
    """
    check_words_and_times(words_and_times)  # 验证输入格式是否正确
    words, times = words_and_times['words'], words_and_times['times']
    pl_idxs = range(len(times))  # 包含每位玩家的索引
    w_idxs = range(len(words))    # 包含每个单词的索引
    # BEGIN PROBLEM 10
    "*** 在此处填写你的代码 ***"
    ans = [[] for _ in pl_idxs]
    for i in w_idxs:
        mn = 0
        for person in pl_idxs:
            if(times[person][i] < times[mn][i]):
                mn = person
        ans[mn] += [words[i]]
    return ans
    # END PROBLEM 10


def check_words_and_times(words_and_times):
    """检查 words_and_times 是否为 {'words': words, 'times': times} 字典，
    并确保 times 中的每个元素都是与 words 等长的数值列表。
    """
    assert 'words' in words_and_times and 'times' in words_and_times and len(words_and_times) == 2
    words, times = words_and_times['words'], words_and_times['times']
    assert all([type(w) == str for w in words]), "words 应为字符串列表"
    assert all([type(t) == list for t in times]), "times 应为列表的列表"
    assert all([isinstance(i, (int, float)) for t in times for i in t]), "times 中的列表应包含数值"
    assert all([len(t) == len(words) for t in times]), "每个单词都应对应一个时间。"


def get_time(times, player_num, word_index):
    """给定 time_per_word 返回的时间列表，返回编号为 player_num 的玩家
    输入索引为 word_index 的单词所花费的时间。"""
    num_players = len(times)
    num_words = len(times[0])
    assert word_index < len(times[0]), f"word_index {word_index} 超出了 0 到 {num_words-1} 的范围"
    assert player_num < len(times), f"player_num {player_num} 超出了 0 到 {num_players-1} 的范围"
    return times[player_num][word_index]


enable_multiplayer = False  # 准备好竞赛时，将其改为 True。

################
# 命令行界面 #
################


def run_typing_test(topics):
    """在命令行中测量打字速度和准确率。"""
    paragraphs = lines_from_file("data/sample_paragraphs.txt")
    random.shuffle(paragraphs)
    select = lambda p: True
    if topics:
        select = about(topics)
    i = 0
    while True:
        source = pick(paragraphs, select, i)
        if not source:
            print("没有更多关于", topics, "的可用段落。")
            return
        print("请输入下面的段落，然后按 Enter/Return 键。")
        print("如果只输入其中一部分，将只根据这一部分评分。\n")
        print(source)
        print()

        start = datetime.now()
        entered = input()
        if not entered:
            print("再见。")
            return
        print()

        elapsed = (datetime.now() - start).total_seconds()
        print("做得不错！")
        print("每分钟字数：", wpm(entered, int(elapsed)))
        print("准确率：    ", accuracy(entered, source))

        print("\n按 Enter/Return 键进入下一段，或输入 q 退出。")
        if input().strip() == "q":
            return
        i += 1


@main
def run(*args):
    """读取命令行参数并调用相应函数。"""
    import argparse

    parser = argparse.ArgumentParser(description="打字测试")
    parser.add_argument("topic", help="主题词", nargs="*")
    parser.add_argument("-t", help="运行打字测试", action="store_true")

    args = parser.parse_args()
    if args.t:
        run_typing_test(args.topic)
