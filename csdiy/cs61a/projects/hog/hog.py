"""Hog 游戏。"""

from dice import six_sided, make_test_dice
from ucb import main, trace, interact

GOAL = 100  # Hog 游戏的目标是获得 100 分。

####################
# 第一阶段：模拟器 #
####################


def roll_dice(num_rolls, dice=six_sided):
    """模拟将 DICE 恰好投掷 NUM_ROLLS 次（NUM_ROLLS > 0）。如果所有结果都
    不是 1，则返回结果之和；否则返回 1。

    num_rolls：要投掷骰子的次数。
    dice：     模拟单次掷骰结果的函数，默认为六面骰。
    """
    # 这些断言语句确保 num_rolls 是正整数。
    assert type(num_rolls) == int, "num_rolls 必须是整数。"
    assert num_rolls > 0, "必须至少投掷一次。"
    # 第 1 题开始
    "*** 在此处编写代码 ***"
    ans = 0

    sow_sad = False

    for i in range(num_rolls):
        temp = dice()
        if(temp == 1):
            sow_sad = True
        else:
            ans += temp

    if sow_sad:
        return 1
    else:
        return ans
    # 第 1 题结束
    


def boar_brawl(player_score, opponent_score):
    """返回当前玩家投掷 0 个骰子时，根据 Boar Brawl 规则获得的分数。

    player_score：  当前玩家的总分。
    opponent_score：另一位玩家的总分。

    """
    # 第 2 题开始
    "*** 在此处编写代码 ***"
    player_fir = player_score % 10
    opponent_sec = opponent_score // 10 % 10

    add_score = 3 * abs(opponent_sec - player_fir)

    return max(1, add_score)
    # 第 2 题结束


def take_turn(num_rolls, player_score, opponent_score, dice=six_sided):
    """当前玩家有 PLAYER_SCORE 分、对手有 OPPONENT_SCORE 分时，
    返回该玩家在一回合中投掷 NUM_ROLLS 个骰子所获得的分数。

    num_rolls：     要投掷骰子的次数。
    player_score：  当前玩家的总分。
    opponent_score：另一位玩家的总分。
    dice：          模拟单次掷骰结果的函数。
    """
    # 请保留这些断言语句；它们有助于检查错误。
    assert type(num_rolls) == int, "num_rolls 必须是整数。"
    assert num_rolls >= 0, "在 take_turn 中不能投掷负数个骰子。"
    assert num_rolls <= 10, "不能投掷超过 10 个骰子。"
    # 第 3 题开始
    "*** 在此处编写代码 ***"
    if num_rolls == 0:
        return boar_brawl(player_score, opponent_score)
    else:
        return roll_dice(num_rolls, dice)
    # 第 3 题结束


def simple_update(num_rolls, player_score, opponent_score, dice=six_sided):
    """返回一名玩家的总分：该玩家以 PLAYER_SCORE 分开始回合，
    随后投掷 NUM_ROLLS 个 DICE，且忽略 Sus Fuss 规则。
    """
    score = player_score + take_turn(num_rolls, player_score, opponent_score, dice)
    return score


def is_prime(n):
    """返回 N 是否为质数。"""
    if n == 1:
        return False
    k = 2
    while k < n:
        if n % k == 0:
            return False
        k += 1
    return True


def num_factors(n):
    """返回 N 的因数个数，包括 1 和 N 本身。"""
    # 第 4 题开始
    "*** 在此处编写代码 ***"
    count = 0
    for i in range(1, n + 1):
        if(n % i == 0):
            count += 1
    return count
    # 第 4 题结束


def sus_points(score):
    """返回考虑 Sus Fuss 规则后玩家的新分数。"""
    # 第 4 题开始
    "*** 在此处编写代码 ***"
    count = num_factors(score)
    if(count == 4 or count == 3):
        while(not is_prime(score)):
            score += 1
    return score
    # 第 4 题结束


def sus_update(num_rolls, player_score, opponent_score, dice=six_sided):
    """返回一名玩家的总分：该玩家以 PLAYER_SCORE 分开始回合，
    随后投掷 NUM_ROLLS 个 DICE，且*应用* Sus Fuss 规则。
    """
    # 第 4 题开始
    "*** 在此处编写代码 ***"
    return sus_points(simple_update(num_rolls, player_score, opponent_score, dice))
    # 第 4 题结束


def always_roll_5(score, opponent_score):
    """无论玩家或对手的分数是多少，始终投掷 5 个骰子的策略。
    """
    return 5


def play(strategy0, strategy1, update, score0=0, score1=0, dice=six_sided, goal=GOAL):
    """模拟一局游戏并返回两名玩家的最终分数，玩家 0 的分数在前，
    玩家 1 的分数在后。

    例如，play(always_roll_5, always_roll_5, sus_update) 模拟一局
    两名玩家每回合都选择投掷 5 个骰子、并应用 Sus Fuss 规则的游戏。

    策略函数（如 always_roll_5）接收当前玩家和对手的分数，并返回
    当前玩家选择投掷的骰子个数。

    更新函数（如 sus_update 或 simple_update）接收要投掷的骰子个数、
    当前玩家的分数、对手的分数，以及用于模拟掷骰子的 dice 函数。
    它返回当前玩家完成回合后的更新分数。

    strategy0：玩家 0 的策略。
    strategy1：玩家 1 的策略。
    update：   更新函数（供两名玩家使用）。
    score0：   玩家 0 的初始分数。
    score1：   玩家 1 的初始分数。
    dice：     模拟一次掷骰且不接收参数的函数。
    goal：     有人达到此分数时游戏结束并获胜。
    """
    who = 0  # 即将行动的玩家：0（先手）或 1（后手）
    # 第 5 题开始
    "*** 在此处编写代码 ***"
    while (score0 < goal and score1 < goal):
        if(who == 0):
            score0 = update(strategy0(score0, score1), score0, score1, dice)
        else:
            score1 = update(strategy1(score1, score0), score1, score0, dice)
        who ^= 1

    # 第 5 题结束
    return score0, score1


####################
# 第二阶段：策略   #
####################


def always_roll(n):
    """返回一个始终投掷 N 个骰子的玩家策略。

    玩家策略是一个接收两个总分（当前玩家的分数和对手的分数）作为参数，
    并返回当前玩家本回合将投掷的骰子个数的函数。

    >>> strategy = always_roll(3)
    >>> strategy(0, 0)
    3
    >>> strategy(99, 99)
    3
    """
    assert n >= 0 and n <= 10

    # 第 6 题开始
    "*** 在此处编写代码 ***"
    def always(a, b):
        return n
    return always
    # 第 6 题结束


def catch_up(score, opponent_score):
    """一种通常投掷 5 个骰子的玩家策略；如果对手分数更高，
    则投掷 6 个骰子。

    >>> catch_up(9, 4)
    5
    >>> strategy(17, 18)
    6
    """
    if score < opponent_score:
        return 6  # 多投掷一个骰子以追赶对手
    else:
        return 5


def is_always_roll(strategy, goal=GOAL):
    """在目标分数为 GOAL 的游戏中，针对 score 和 opponent_score 的
    每一种可能组合，返回 STRATEGY 是否始终选择投掷相同数量的骰子。

    >>> is_always_roll(always_roll_5)
    True
    >>> is_always_roll(always_roll(3))
    True
    >>> is_always_roll(catch_up)
    False
    """
    # 第 7 题开始
    "*** 在此处编写代码 ***"
    seam = True
    for i in range(goal):
        for j in range(goal):
            if(strategy(i, j) != strategy(1, 1)):
                seam = False
    return seam
    # 第 7 题结束


def make_averaged(original_function, times_called=1000):
    """返回一个函数，该函数会调用 ORIGINAL_FUNCTION 共 TIMES_CALLED 次，
    并返回所得结果的平均值。

    实现此函数时需要使用 *args 语法。

    >>> dice = make_test_dice(4, 2, 5, 1)
    >>> averaged_dice = make_averaged(roll_dice, 40)
    >>> averaged_dice(1, dice)  # 10 个 4、10 个 2、10 个 5 和 10 个 1 的平均值
    3.0
    """

    # 第 8 题开始
    "*** 在此处编写代码 ***"
    def average(*args):
        sum = 0
        for i in range(times_called):
            sum += original_function(*args)
        return sum / times_called

    return average
    # 第 8 题结束


def max_scoring_num_rolls(dice=six_sided, times_called=1000):
    """返回能使一回合平均得分最高的骰子个数（1 到 10）。
    假设骰子的结果始终为正数。

    >>> dice = make_test_dice(1, 6)
    >>> max_scoring_num_rolls(dice)
    1
    """
    # 第 9 题开始
    "*** 在此处编写代码 ***"
    ans = 1
    val = 0
    average = make_averaged(roll_dice, times_called)
    for i in range(1, 11):
        temp = average(i, dice)
        if(temp > val):
            ans = i
            val = temp
    return ans
    # 第 9 题结束


def winner(strategy0, strategy1):
    """如果 strategy0 战胜 strategy1，则返回 0；否则返回 1。"""
    score0, score1 = play(strategy0, strategy1, sus_update)
    if score0 > score1:
        return 0
    else:
        return 1


def average_win_rate(strategy, baseline=always_roll(6)):
    """返回 STRATEGY 对阵 BASELINE 时的平均胜率。该结果取分别以玩家 0
    和玩家 1 身份开始游戏时胜率的平均值。
    """
    win_rate_as_player_0 = 1 - make_averaged(winner)(strategy, baseline)
    win_rate_as_player_1 = make_averaged(winner)(baseline, strategy)

    return (win_rate_as_player_0 + win_rate_as_player_1) / 2


def run_experiments():
    """运行一系列策略实验并报告结果。"""
    six_sided_max = max_scoring_num_rolls(six_sided)
    print("六面骰能获得最高平均分的投掷个数：", six_sided_max)

    print("always_roll(6) 的胜率：", average_win_rate(always_roll(6)))  # 接近 0.5
    print("catch_up 的胜率：", average_win_rate(catch_up))
    print("always_roll(3) 的胜率：", average_win_rate(always_roll(3)))
    print("always_roll(8) 的胜率：", average_win_rate(always_roll(8)))

    print("boar_strategy 的胜率：", average_win_rate(boar_strategy))
    print("sus_strategy 的胜率：", average_win_rate(sus_strategy))
    print("final_strategy 的胜率：", average_win_rate(final_strategy))
    "*** 你可以按需添加其他实验 ***"




def boar_strategy(score, opponent_score, threshold=11, num_rolls=6):
    """如果 Boar Brawl 能带来至少 THRESHOLD 分，此策略返回 0；
    否则返回 NUM_ROLLS。忽略 Sus Fuss 规则。
    """
    # 第 10 题开始
    if(boar_brawl(score, opponent_score) >= threshold):
        return 0
    else:
        return num_rolls
    #return num_rolls  # 完成实现后删除此行。
    # 第 10 题结束


def sus_strategy(score, opponent_score, threshold=11, num_rolls=6):
    """当投掷 0 个骰子能使分数至少增加 THRESHOLD 分时，此策略返回 0；
    否则返回 NUM_ROLLS。同时考虑 Boar Brawl 和 Suss Fuss 规则。"""
    # 第 11 题开始
    if(sus_update(0, score, opponent_score) - score >= threshold):
        return 0
    else:
        return num_rolls
        
    return num_rolls  # 完成实现后删除此行。
    # 第 11 题结束


def final_strategy(score, opponent_score):
    """简要描述你的最终策略。

    *** 在此处填写你的描述 ***
    """
    # 第 12 题开始
    return 6  # 完成实现后删除此行。
    # 第 12 题结束


################
# 命令行界面   #
################

# 注意：本节中的函数无需修改。它使用了课程尚未讲解的 Python 特性。


@main
def run(*args):
    """读取命令行参数并调用相应的函数。"""
    import argparse

    parser = argparse.ArgumentParser(description="运行 Hog 游戏")
    parser.add_argument(
        "--run_experiments", "-r", action="store_true", help="运行策略实验"
    )

    args = parser.parse_args()

    if args.run_experiments:
        run_experiments()
