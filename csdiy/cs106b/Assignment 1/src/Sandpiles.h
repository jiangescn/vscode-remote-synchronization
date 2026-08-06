/******************************************************************************
 * 文件：Sandpiles.h
 * 作者：Keith Schwarz（htiek@cs.stanford.edu）
 *
 * 作业中 Sandpiles 部分的头文件。你不应
 * 修改此文件。
 */

#ifndef Sandpile_Included
#define Sandpile_Included

#include "grid.h"

/**
 * 在指定位置向特定世界中落下一粒沙子。
 *
 * 如果位置越界，此函数不产生任何效果，网格
 * 保持不变。
 *
 * 这可能触发倒塌，并传播到网格中的其他位置。
 * 当单元格达到四粒沙子时会倒塌；倒塌时会被清空
 * 并在四个相邻单元格中的每个位置落下一粒沙子。
 *
 * @param world 沙子要落入的网格。
 * @param row 沙子落入的行。
 * @param col 沙子落入的列。
 */
void dropSandOn(Grid<int>& world, int row, int col);

#endif
