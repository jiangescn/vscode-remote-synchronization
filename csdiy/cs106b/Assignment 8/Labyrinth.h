#ifndef Labyrinth_Included
#define Labyrinth_Included

#include "GUI/MemoryDiagnostics.h"
#include <string>

/**
 * 表示迷宫中物品的类型。
 */
enum class Item {
    NOTHING, SPELLBOOK, POTION, WAND
};

/**
 * 表示迷宫中单元格的类型。
 */
struct MazeCell {
    Item whatsHere; // 存在的是哪个物品（如果有）。

    MazeCell* north;
    MazeCell* south;
    MazeCell* east;
    MazeCell* west;
};

/**
 * 给定迷宫中的位置，返回给定移动序列是否
 * 这些步骤将让你逃出迷宫。
 *
 * 要逃离迷宫，你需要找到药水、法术书和
 * 魔杖。你只能沿四个基本方向移动，
 * 不能朝迷宫中不存在的方向移动。
 */
bool isPathToFreedom(MazeCell* start, const std::string& moves);




/**
 * 我们为你提供此函数，以便你可以按需
 * 将 Item 变量存储在 HashMap 或 HashSet 中。
 */
inline int hashCode(Item item) {
    return static_cast<int>(item);
}

#endif
