#ifndef MazeGenerator_Included
#define MazeGenerator_Included

#include "../Labyrinth.h"
#include "grid.h"
#include "vector.h"
#include <string>

/**
 * 给定迷宫的图形表示，返回 Grid<MazeCell*>
 * 包含该迷宫的内容。
 *
 * 例如，以下是表示第一个示例时应提供的输入
 * 讲义中的迷宫：
 *
 *         {"* *-W *",
 *          "| |   |",
 *          "*-* * *",
 *          "  | | |",
 *          "S *-*-*",
 *          "|   | |",
 *          "*-*-* P"}
 *
 * 这里，星号表示空位，其余字母表示
 * 魔杖、法术书和药水所在的位置。（由于我们将整个迷宫
 * 返回给你，你可以选择从何处开始。）| 和 - 符号
 * 用于表示哪些单元格链接到哪些其他单元格。
 *
 * 迷宫可以具有任意大小和任意数量的物品副本，尽管
 * “真正的”迷宫中每种物品只会有一个。
 */
Grid<MazeCell*> toMaze(const Vector<std::string>& textMaze);

/**
 * 返回大小为 numRows x numCols、专门针对以下内容定制的迷宫
 * 给定的名称。
 *
 * 我们已经为你实现此函数。你无需编写它
 * 你自己。
 *
 * 请不要对此函数进行任何更改——我们将使用自己的
 * 在测试你的代码时使用参考版本；如果
 * 你解决的迷宫并不是我们希望你解决的迷宫！
 */
MazeCell* mazeFor(const std::string& name);

/**
 * 返回具有指定节点数的 Twisty Maze。
 *
 * 请不要对此函数进行任何更改——我们将使用自己的
 * 在测试你的代码时使用参考版本；如果
 * 你解决的迷宫并不是我们希望你解决的迷宫！
 */
MazeCell* twistyMazeFor(const std::string& name);

#endif
