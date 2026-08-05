"""蚂蚁大战蜜蜂。"""

from __future__ import annotations  # 这使类型注解能够正常工作
import random
from ucb import main, interact, trace
from collections import OrderedDict

################
# 核心类 #
################


class Place:
    """一个 Place 容纳昆虫，并有通往另一个 Place 的出口。"""
    is_hive = False

    def __init__(self, name: str, exit: Place | None = None):
        """使用给定的 NAME 和 EXIT 创建 Place。

        name —— 字符串，表示该 Place 的名称。
        exit —— 离开当前 Place 后到达的 Place（可以是 None）。
        """
        self.name = name
        self.exit = exit
        self.bees: list[Bee] = []
        self.ant: Ant | None = None
        self.entrance: Place | None = None
        # 第 1 阶段：为出口添加入口
        # BEGIN Problem 2
        "*** YOUR CODE HERE ***"
        if(self.exit):
            self.exit.entrance = self
        # END Problem 2

    def add_insect(self, insect: Insect):
        """让昆虫把自身加入此位置。该方法单独存在，以便子类重写。
        """
        insect.add_to(self)

    def remove_insect(self, insect: Insect):
        """让昆虫把自身从此位置移除。该方法单独存在，以便子类重写。
        """
        insect.remove_from(self)

    def __str__(self) -> str:
        return self.name


class Insect:
    """Insect 是 Ant 与 Bee 的基类，具有生命值和所在 Place。"""

    next_id = 0  # 每只昆虫都获得唯一的 ID 编号
    damage = 0
    is_waterproof = False
    # 在此添加类属性

    def __init__(self, health: int, place: Place | None = None):
        """使用生命值和起始 PLACE 创建 Insect。"""
        self.health = health
        self.full_health = health
        self.place = place

        # 为每只昆虫分配唯一 ID
        self.id = Insect.next_id
        Insect.next_id += 1

    def reduce_health(self, damage_taken: float):
        """把生命值减少 DAMAGE_TAKEN；若生命值耗尽，就从所在位置移除该昆虫。此方法在 gui.py 中经过装饰以支持 GUI。

        >>> test_insect = Insect(5)
        >>> test_insect.reduce_health(2)
        >>> test_insect.health
        3
        """
        self.health -= damage_taken
        if self.health <= 0:
            self.zero_health_callback()

            if self.place is not None:
                self.place.remove_insect(self)

    def action(self, gamestate: GameState):
        """每回合执行的动作。"""

    def zero_health_callback(self):
        """
        生命值降到 0 或更低时调用。
        在 gui.py 中经过装饰以支持 GUI。
        """

    def add_to(self, place: Place):
        self.place = place

    def remove_from(self, place: Place):
        self.place = None

    def __repr__(self):
        cname = type(self).__name__
        return '{0}({1}, {2})'.format(cname, self.health, self.place)


class Ant(Insect):
    """一只 Ant 占据一个位置，并为蚁群工作。"""

    implemented = False  # 只应实例化已经实现的 Ant 类
    food_cost = 0
    is_container = False
    # 在此添加类属性

    def __init__(self, health: int = 1):
        super().__init__(health)

    def can_contain(self, other: Ant) -> bool:
        return False

    def store_ant(self, ant: Ant):
        assert False, "{0} cannot contain an ant".format(self)

    def remove_ant(self, ant: Ant):
        assert False, "{0} cannot contain an ant".format(self)

    def add_to(self, place: Place):
        if place.ant is None:
            place.ant = self
        else:
            # BEGIN Problem 8b
            if place.ant.can_contain(self):
                place.ant.store_ant(self)
            elif self.can_contain(place.ant):
                self.store_ant(place.ant)
                place.ant = self
            else:
                assert place.ant is None, 'Too many ants in {0}'.format(place)
            # END Problem 8b
        Insect.add_to(self, place)

    def remove_from(self, place: Place):
        if place.ant is self:
            place.ant = None
        elif place.ant is None:
            assert False, '{0} is not in {1}'.format(self, place)
        else:
            place.ant.remove_ant(self)
        Insect.remove_from(self, place)

    def double(self):
        """如果这只蚂蚁的伤害尚未翻倍，就将其翻倍。"""
        # BEGIN Problem 12
        "*** YOUR CODE HERE ***"
        if not getattr(self, 'damage_double', False):
            self.damage *= 2
            self.damage_double = True
        # END Problem 12


class HarvesterAnt(Ant):
    """HarvesterAnt 每回合为蚁群额外生产 1 份食物。"""

    name = 'Harvester'
    implemented = True
    # 在此重写类属性
    food_cost = 2

    def action(self, gamestate: GameState):
        """为蚁群额外生产 1 份食物。

        gamestate —— GameState，用于访问游戏状态信息。
        """
        # BEGIN Problem 1
        "*** YOUR CODE HERE ***"
        gamestate.food += 1


        # END Problem 1


class ThrowerAnt(Ant):
    """ThrowerAnt 每回合向射程内最近的 Bee 投掷一片叶子。"""

    name = 'Thrower'
    implemented = True
    damage = 1
    # 在此添加或重写类属性
    food_cost = 3
    lower_bound = 0
    upper_bound = float('inf')

    def nearest_bee(self) -> Bee | None:
        """沿 entrance 从 ThrowerAnt 所在位置向前搜索，在最近的、含 Bee 且不是 Hive 的 Place 中随机返回一只 Bee。
        若不存在这样的 Bee（或射程内没有），该方法返回 None。
        """
        if not self.place:
            return None  # 不在任何 Place 中的 Ant 没有最近的 Bee
        current_place = self.place
        distance = 0
        # BEGIN Problem 3 and 4
        while (current_place != None and not current_place.is_hive):
            if(self.lower_bound <= distance <= self.upper_bound and current_place.bees):
                return random_bee(current_place.bees)
            current_place = current_place.entrance
            distance += 1   
        return random_bee(self.place.bees) # REPLACE THIS LINE
        # END Problem 3 and 4

    def throw_at(self, target: Bee | None):
        """向目标 Bee 投掷叶子，降低其生命值。"""
        if target is not None:
            target.reduce_health(self.damage)

    def action(self, gamestate: GameState):
        """向射程内最近的 Bee 投掷叶子。"""
        self.throw_at(self.nearest_bee())


def random_bee(bees: list[Bee]) -> Bee | None:
    """从蜜蜂列表中随机返回一只；若列表为空则返回 None。"""
    assert isinstance(bees, list), \
        "random_bee's argument should be a list but was a %s" % type(bees).__name__
    if bees:
        return random.choice(bees)

##############
# 扩展 #
##############


class ShortThrower(ThrowerAnt):
    """一种 ThrowerAnt，只攻击最多相距 3 个位置的 Bee。"""

    name = 'Short'
    food_cost = 2
    # 在此重写类属性
    
    # BEGIN Problem 4
    upper_bound = 3
    implemented = True   # 改为 True 即可在 GUI 中查看
    # END Problem 4


class LongThrower(ThrowerAnt):
    """一种 ThrowerAnt，只攻击至少相距 5 个位置的 Bee。"""

    name = 'Long'
    food_cost = 2
    # 在此重写类属性
    # BEGIN Problem 4
    lower_bound = 5
    implemented = True   # 改为 True 即可在 GUI 中查看
    # END Problem 4


class FireAnt(Ant):
    """FireAnt 阵亡时会烧伤同一 Place 中的所有 Bee。"""

    name = 'Fire'
    damage = 3
    food_cost = 5
    # 在此重写类属性
    # BEGIN Problem 5
    implemented = True   # 改为 True 即可在 GUI 中查看
    # END Problem 5

    def __init__(self, health: int = 3):
        """创建一只生命值为 HEALTH 的 Ant。"""
        super().__init__(health)

    def reduce_health(self, damage_taken: float):
        """把生命值减少 DAMAGE_TAKEN；若 FireAnt 生命值耗尽，就将它从所在位置移除。请确保当前 Place 中每只 Bee 的生命值都被降低；若 FireAnt 阵亡，还要施加额外伤害。
        """
        # BEGIN Problem 5
        "*** YOUR CODE HERE ***"
        place = self.place
        will_die = damage_taken >= self.health   

        reflected_damage = damage_taken
        if(will_die):
            reflected_damage += self.damage

        super().reduce_health(damage_taken)

        if(place != None):
            for bee in place.bees[:]:
                bee.reduce_health(reflected_damage)

        # END Problem 5

# BEGIN Problem 6
# WallAnt 类
class WallAnt(Ant):
    name = 'Wall'
    food_cost = 4
    implemented = True

    def __init__(self, health: int = 4):
        super().__init__(health)

# END Problem 6

# BEGIN Problem 7
# HungryAnt 类
class HungryAnt(Ant):
    name = 'Hungry'
    food_cost = 4
    implemented = True

    chew_cooldown = 3

    def __init__(self, health: int = 1):
        super().__init__(health)
        self.cooldown = 0

    def action(self, gamestate: GameState):

        place = self.place
        if place == None:
            return

        if (self.cooldown > 0):
            self.cooldown -= 1
        else:
            bee = random_bee(place.bees)

            if(bee != None):
                bee.reduce_health(bee.health)
                self.cooldown = self.chew_cooldown
# END Problem 7


class ContainerAnt(Ant):
    """
    ContainerAnt 可以容纳其他蚂蚁，从而与它们共享位置。
    """
    is_container = True

    def __init__(self, health: int):
        super().__init__(health)
        self.ant_contained = None

    def can_contain(self, other: Ant) -> bool:
        # BEGIN Problem 8a
        "*** YOUR CODE HERE ***"
        return self.ant_contained is None and not other.is_container
        # END Problem 8a

    def store_ant(self, ant: Ant):
        # BEGIN Problem 8a
        "*** YOUR CODE HERE ***"
        self.ant_contained = ant
        # END Problem 8a

    def remove_ant(self, ant: Ant):
        if self.ant_contained is not ant:
            assert False, "{} does not contain {}".format(self, ant)
        self.ant_contained = None

    def remove_from(self, place: Place):
        # 对容器蚂蚁进行特殊处理
        if place.ant is self:
            # 容器已被移除，其中容纳的蚂蚁应留在游戏中
            place.ant = self.ant_contained
            Insect.remove_from(self, place)
        else:
            # 默认采用普通行为
            Ant.remove_from(self, place)

    def action(self, gamestate: GameState):
        # BEGIN Problem 8a
        "*** YOUR CODE HERE ***"
        if(self.ant_contained is not None):
            self.ant_contained.action(gamestate)
        # END Problem 8a


class ProtectorAnt(ContainerAnt):
    """ProtectorAnt 为其他 Ant 提供保护。"""

    name = 'Protector'
    food_cost = 4
    # 在此重写类属性
    # BEGIN Problem 8c
    implemented = True   # 改为 True 即可在 GUI 中查看

    def __init__(self, health: int = 2):
        super().__init__(health)
    # END Problem 8c

# BEGIN Problem 9
# TankAnt 类
class TankAnt(ContainerAnt):
    name = 'Tank'
    food_cost = 6
    damage = 1
    implemented = True

    def __init__(self, health: int = 2):
        super().__init__(health)

    def action(self, gamestate: GameState):
        place = self.place
        if(place is not None):
            for bee in place.bees[:]:
                bee.reduce_health(self.damage)

        super().action(gamestate)
# END Problem 9


class Water(Place):
    """Water 是只能容纳防水昆虫的位置。"""

    def add_insect(self, insect: Insect):
        """把 Insect 加入此位置。若该昆虫不防水，把其生命值降为 0。"""
        # BEGIN Problem 10
        "*** YOUR CODE HERE ***"
        Place.add_insect(self, insect)
        if(not insect.is_waterproof):
            insect.reduce_health(insect.health)
        # END Problem 10

# BEGIN Problem 11
# ScubaThrower 类
class ScubaThrower(ThrowerAnt):
    name = 'Scuba'
    food_cost = 6
    is_waterproof = True
    implemented = True

# END Problem 11


class QueenAnt(ThrowerAnt):
    """QueenAnt 会增强她身后所有蚂蚁的伤害。"""

    name = 'Queen'
    food_cost = 7
    # 在此重写类属性
    # BEGIN Problem 12
    implemented = True   # 改为 True 即可在 GUI 中查看
    # END Problem 12

    def action(self, gamestate: GameState):
        """QueenAnt 会投掷叶子，同时让她所在隧道中的蚂蚁伤害翻倍。
        """
        # BEGIN Problem 12
        "*** YOUR CODE HERE ***"
        super().action(gamestate)
        assert self.place is not None
        current_place = self.place.exit

        while(current_place is not None):
            ant = current_place.ant

            if(ant is not None):
                ant.double()

                if(ant.is_container and ant.ant_contained is not None): # type: ignore
                    ant.ant_contained.double() # type: ignore

            current_place = current_place.exit
        # END Problem 12

    def reduce_health(self, damage_taken: float):
        """把生命值减少 DAMAGE_TAKEN；若 QueenAnt 生命值耗尽，发出游戏结束信号。
        """
        # BEGIN Problem 12
        "*** YOUR CODE HERE ***"
        super().reduce_health(damage_taken)
        if(self.health <= 0):
            ants_lose()
        # END Problem 12


################
# 额外挑战 #
################

class SlowThrower(ThrowerAnt):
    """一种会使 Bee 减速的 ThrowerAnt。"""

    name = 'Slow'
    food_cost = 6
    # BEGIN Problem EC 1
    implemented = False   # 改为 True 即可在 GUI 中查看
    # END Problem EC 1

    def throw_at(self, target: Bee | None):
        # BEGIN Problem EC 1
        "*** YOUR CODE HERE ***"
        # END Problem EC 1


class ScaryThrower(ThrowerAnt):
    """一种会恐吓 Bee、使其后退而非前进的 ThrowerAnt。"""

    name = 'Scary'
    food_cost = 6
    # BEGIN Problem EC 2
    implemented = False   # 改为 True 即可在 GUI 中查看
    # END Problem EC 2

    def throw_at(self, target: Bee | None):
        # BEGIN Problem EC 2
        "*** YOUR CODE HERE ***"
        # END Problem EC 2


class NinjaAnt(Ant):
    """NinjaAnt 不会阻挡道路，并伤害同一位置中的所有蜜蜂。"""

    name = 'Ninja'
    damage = 1
    food_cost = 5
    # 在此重写类属性
    # BEGIN Problem EC 3
    implemented = False   # 改为 True 即可在 GUI 中查看
    # END Problem EC 3

    def action(self, gamestate: GameState):
        # BEGIN Problem EC 3
        "*** YOUR CODE HERE ***"
        # END Problem EC 3


class LaserAnt(ThrowerAnt):
    """一种会伤害路径上所有 Insect 的 ThrowerAnt。"""

    name = 'Laser'
    food_cost = 10
    # 在此重写类属性
    # BEGIN Problem EC 4
    implemented = False   # 改为 True 即可在 GUI 中查看
    # END Problem EC 4

    def __init__(self, health: int = 1):
        super().__init__(health)
        self.insects_shot = 0

    def insects_in_front(self) -> dict[Bee, int]:
        # BEGIN Problem EC 4
        return {}
        # END Problem EC 4

    def calculate_damage(self, distance: int) -> float:
        # BEGIN Problem EC 4
        return 0
        # END Problem EC 4

    def action(self, gamestate: GameState):
        insects_and_distances = self.insects_in_front()
        LaserAnt.play_sound_effect() # 激光束音效
        for insect, distance in insects_and_distances.items():
            damage = self.calculate_damage(distance)
            insect.reduce_health(damage)
            if damage:
                self.insects_shot += 1

    @classmethod
    def play_sound_effect(cls):
        """播放激光音效；此方法在 gui.py 中经过装饰。"""
        pass


########
# 蜜蜂 #
########

class Bee(Insect):
    """Bee 沿出口在位置之间移动，并蜇伤蚂蚁。"""

    name = 'Bee'
    damage = 1
    is_waterproof = True


    def sting(self, ant: Ant):
        """攻击一只 ANT，使其生命值减少 1。"""
        ant.reduce_health(self.damage)

    def move_to(self, place: Place):
        """把 Bee 从当前 Place 移到新的 PLACE。"""
        if self.place is not None:
            self.place.remove_insect(self)

        if place is not None:
            place.add_insect(self)

    def blocked(self) -> bool:
        """如果该 Bee 无法前进到下一个 Place，返回 True。"""
        # 对 NinjaAnt 进行特殊处理
        # BEGIN Problem EC 3
        return self.place is not None and self.place.ant is not None
        # END Problem EC 3

    def action(self, gamestate: GameState):
        """如果出口被阻挡，Bee 的动作是蜇伤挡路的 Ant；否则移动到当前 Place 的出口。

        gamestate —— GameState，用于访问游戏状态信息。
        """
        destination = None
        if self.place:
            destination = self.place.exit


        if self.blocked() and self.place and self.place.ant:
            self.sting(self.place.ant)
        elif self.health > 0 and destination is not None:
            self.move_to(destination)

    def add_to(self, place: Place):
        place.bees.append(self)
        super().add_to(place)

    def remove_from(self, place: Place):
        place.bees.remove(self)
        super().remove_from(place)

    def scare(self, length: int):
        """
        如果该 Bee 以前未被恐吓过，让它尝试向后移动 LENGTH 次。
        """
        # BEGIN Problem EC 2
        "*** YOUR CODE HERE ***"
        # END Problem EC 2


class Wasp(Bee):
    """伤害更高的一类 Bee。"""
    name = 'Wasp'
    damage = 2


class Boss(Wasp):
    """蜜蜂首领；任何攻击对 Boss 造成的伤害都有上限。
    """
    name = 'Boss'
    damage_cap = 8

    def reduce_health(self, damage_taken: float):
        super().reduce_health(min(damage_taken, self.damage_cap))

    @classmethod
    def play_sound_effect(cls):
        "Boss 到达时播放音效；此方法在 gui.py 中经过装饰。"
        pass


class Hive(Place):
    """蜜蜂发起进攻的 Place。

    assault_plan —— AssaultPlan，记录蜜蜂进入蚁群的时间和位置。
    """
    is_hive = True

    def __init__(self, assault_plan: AssaultPlan):
        self.name = 'Hive'
        self.assault_plan = assault_plan
        self.bees: list[Bee] = []
        for bee in assault_plan.all_bees():
            self.add_insect(bee)
        # 对 Hive 而言，下列属性始终为 None
        self.entrance: None = None
        self.ant: None = None
        self.exit: Place | None = None

    def strategy(self, gamestate: GameState):
        exits = [p for p in gamestate.places.values() if p.entrance is self]

        for bee in self.assault_plan.get(gamestate.time, []):
            if Boss in bee.__class__.__mro__:
                Boss.play_sound_effect()
                GameState.display_notification('Boss Bee is Here!')
            bee.move_to(random.choice(exits))
            gamestate.active_bees.append(bee)

###################
# 游戏组件 #
###################

class GameState:
    """管理全局游戏状态并模拟时间推进的蚁群。

    属性：
    time —— 已经过的时间
    food —— 蚁群当前可用的食物总量
    places —— 蚁群中所有位置的列表（包括 Hive）
    bee_entrances —— 蜜蜂可以进入的位置列表
    """

    def __init__(self, beehive: Hive, ant_types: list, create_places, dimensions, food: int = 2):
        """创建用于模拟游戏的 GameState。

        参数：
        beehive —— 装满蜜蜂的 Hive
        ant_types —— 蚂蚁类列表
        create_places —— 创建位置集合的函数
        dimensions —— 包含游戏布局尺寸的二元组
        """
        self.time: int = 0
        self.food = food
        self.beehive = beehive
        self.ant_types = OrderedDict((a.name, a) for a in ant_types)
        self.dimensions = dimensions
        self.active_bees: list = []
        self.configure(beehive, create_places)

    def configure(self, beehive: Hive, create_places):
        """配置蚁群中的各个位置。"""
        self.base: AntHomeBase = AntHomeBase('Ant Home Base')
        self.places: OrderedDict = OrderedDict()
        self.bee_entrances: list = []

        def register_place(place: Place, is_bee_entrance: bool):
            self.places[place.name] = place
            if is_bee_entrance:
                place.entrance = beehive
                self.bee_entrances.append(place)
        register_place(self.beehive, False)
        create_places(self.base, register_place,
                      self.dimensions[0], self.dimensions[1])

    def ants_take_actions(self): # 让蚂蚁执行动作
        for ant in self.ants:
            if ant.health > 0:
                ant.action(self)

    def bees_take_actions(self, num_bees: int) -> int: # 让蜜蜂执行动作
        for bee in self.active_bees[:]:
            if bee.health > 0:
                bee.action(self)
            if bee.health <= 0:
                num_bees -= 1
                self.active_bees.remove(bee)
        if num_bees == 0: # 检查玩家是否获胜
            GameState.play_win_sound()
            raise AntsWinException()
        return num_bees

    def simulate(self):
        """模拟一次对蚁群的进攻；GUI 会调用它来运行游戏。"""
        num_bees = len(self.bees)
        try:
            while True:
                self.beehive.strategy(self) # 蜜蜂从蜂巢入侵
                yield None # 产出状态后，玩家有时间放置蚂蚁
                self.ants_take_actions()
                self.time += 1
                yield None # 产出状态后，等待投叶动画播放完毕，再让蜜蜂行动
                num_bees = self.bees_take_actions(num_bees)
        except AntsWinException:
            print('All bees are vanquished. You win!')
            yield True
        except AntsLoseException:
            print('The bees reached homebase or the queen ant queen has perished. Please try again :(')
            yield False

    def deploy_ant(self, place_name: str, ant_type_name: str) -> Ant | None:
        """如果食物充足，就放置一只蚂蚁。当前策略会调用该方法部署蚂蚁。
        """
        ant_type = self.ant_types[ant_type_name]
        if ant_type.food_cost > self.food:
            message = 'Not enough food!'
            print(message)
            GameState.display_notification(message)
        else:
            ant: Ant = ant_type()
            self.places[place_name].add_insect(ant)
            self.food -= ant.food_cost
            return ant

    def remove_ant(self, place_name: str):
        """从游戏中移除一只 Ant。"""
        place = self.places[place_name]
        if place.ant is not None:
            place.remove_insect(place.ant)

    @staticmethod
    def display_notification(message):
        """显示通知；此方法在 gui.py 中经过装饰以支持 GUI。"""
        pass

    @classmethod
    def play_win_sound(cls):
        """蚂蚁获胜时播放音效；此方法在 gui.py 中经过装饰。"""
        pass

    @property
    def ants(self):
        return [p.ant for p in self.places.values() if p.ant is not None]

    @property
    def bees(self):
        return [b for p in self.places.values() for b in p.bees]

    @property
    def insects(self):
        return self.ants + self.bees

    def __str__(self):
        status = ' (Food: {0}, Time: {1})'.format(self.food, self.time)
        return str([str(i) for i in self.ants + self.bees]) + status


class AntHomeBase(Place):
    """位于隧道末端、蚁后通常居住的 AntHomeBase。"""

    def add_insect(self, insect):
        """把 Insect 加入此 Place。实际上不能把 Ant 加入 AntHomeBase；如果 Bee 试图进入 AntHomeBase，就抛出 AntsLoseException，表示游戏结束。
        """
        assert isinstance(insect, Bee), 'Cannot add {0} to AntHomeBase'
        raise AntsLoseException()


def ants_win():
    """发出蚂蚁获胜的信号。"""
    raise AntsWinException()


def ants_lose():
    """发出蚂蚁失败的信号。"""
    raise AntsLoseException()


def ant_types() -> list:
    """返回所有已实现 Ant 类的列表。"""
    all_ant_types: list = []
    new_types: list = [Ant]
    while new_types:
        new_types = [t for c in new_types for t in c.__subclasses__()]
        all_ant_types.extend(new_types)
    return [t for t in all_ant_types if t.implemented]


def bee_types() -> list:
    """返回所有已实现 Bee 类的列表。"""
    all_bee_types: list = []
    new_types: list = [Bee]
    while new_types:
        new_types = [t for c in new_types for t in c.__subclasses__()]
        all_bee_types.extend(new_types)
    return all_bee_types


class GameOverException(Exception):
    """游戏结束异常的基类。"""
    pass


class AntsWinException(GameOverException):
    """表示蚂蚁获胜的异常。"""
    pass


class AntsLoseException(GameOverException):
    """表示蚂蚁失败的异常。"""
    pass


###########
# 布局 #
###########


def wet_layout(queen: AntHomeBase, register_place, tunnels: int = 3, length: int = 9, moat_frequency: int = 3):
    """注册由水域和陆地位置混合组成的布局。"""
    for tunnel in range(tunnels):
        exit = queen
        for step in range(length):
            if moat_frequency != 0 and (step + 1) % moat_frequency == 0:
                exit = Water('water_{0}_{1}'.format(tunnel, step), exit)
            else:
                exit = Place('tunnel_{0}_{1}'.format(tunnel, step), exit)
            register_place(exit, step == length - 1)


def dry_layout(queen: AntHomeBase, register_place, tunnels: int = 3, length: int = 9):
    """注册干燥隧道。"""
    wet_layout(queen, register_place, tunnels, length, 0)


#################
# 进攻计划 #
#################

class AssaultPlan(dict):
    """蜜蜂进攻蚁群的计划；攻击按时间分波到来。

    AssaultPlan 是从时间（int）到蜜蜂波次（Bee 列表）的字典。

    >>> AssaultPlan().add_wave(4, 2)
    {4: [Bee(3, None), Bee(3, None)]}
    """
    def add_wave(self, bee_type, bee_health: int, time: int, count: int) -> AssaultPlan:
        """在指定时间添加一波 count 只具有给定生命值的 Bee。"""
        bees = [bee_type(bee_health) for _ in range(count)]
        self.setdefault(time, []).extend(bees)
        return self

    def all_bees(self) -> list:
        """把所有 Bee 放入蜂巢，并返回 Bee 列表。"""
        return [bee for wave in self.values() for bee in wave]