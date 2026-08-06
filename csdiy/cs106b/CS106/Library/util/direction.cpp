/*
 * 文件：direction.cpp
 * -------------------
 * 此文件实现 direction.h 接口。
 *
 * @version 2016/08/04
 * - 修复 operator >>，使其不抛出错误
 * @version 2014/10/08
 * - 移除“using namespace”语句
 */

#include "direction.h"
#include "error.h"
#include "strlib.h"
#include "tokenscanner.h"

/*
 * 实现说明：leftFrom、rightFrom、opposite
 * ---------------------------------------------------
 * 这些函数使用取余运算符循环遍历
 * 枚举类型的内部值。请注意 leftFrom
 * 函数不能从方向减 1，因为结果
 * 之后可能为负数；加 3 能达到相同效果，但
 * 确保值保持为正数。
 */

Direction leftFrom(Direction dir) {
    return Direction((dir + 3) % 4);
}

Direction rightFrom(Direction dir) {
    return Direction((dir + 1) % 4);
}

Direction opposite(Direction dir) {
    return Direction((dir + 2) % 4);
}

/*
 * 实现说明：directionToString
 * ---------------------------------------
 * C++ 编译器要求 default 子句，以确保
 * 函数始终返回字符串，即使方向不是
 * 合法值。
 */

std::string directionToString(Direction dir) {
    switch (dir) {
    case NORTH:
        return "NORTH";
    case EAST:
        return "EAST";
    case SOUTH:
        return "SOUTH";
    default:
    // case WEST:
        return "WEST";   // BUG 修复 2014/07/09：移除不可达的“default”分支
    }
}

/*
 * 实现说明：<<
 * ------------------------
 * 此运算符在输出后必须按引用返回该流
 * 该值。operator << 返回此流，因此该函数
 * 可以实现为单行代码。
 */

std::ostream& operator <<(std::ostream& os, const Direction& dir) {
    return os << directionToString(dir);
}

/*
 * 实现说明：>>
 * ------------------------
 * 此实现使用 TokenScanner 从
 * 流。
 */

std::istream& operator >>(std::istream& is, Direction& dir) {
    TokenScanner scanner(is);
    scanner.ignoreWhitespace();
    std::string token = toUpperCase(scanner.nextToken());
    if (token == "") {
        dir = Direction(-1);
    } else if (startsWith("NORTH", token)) {
        dir = NORTH;
    } else if (startsWith("EAST", token)) {
        dir = EAST;
    } else if (startsWith("SOUTH", token)) {
        dir = SOUTH;
    } else if (startsWith("WEST", token)) {
        dir = WEST;
    } else {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    return is;
}

/*
 * 实现说明：++
 * ------------------------
 * 该运算符签名中的 int 参数是一个标记，用于
 * 由 C++ 编译器用于识别运算符的后缀形式。请注意
 * 使包含 WEST 的变量递增后的值将是
 * 超出 Direction 范围。如果
 * 此运算符只用于其所定义的 for 循环惯用写法。
 */

Direction operator ++(Direction& dir, int) {
    Direction old = dir;
    dir = Direction(dir + 1);
    return old;
}
