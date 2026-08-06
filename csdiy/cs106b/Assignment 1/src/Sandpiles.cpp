/* 文件：Sandpiles.cpp
 *
 * TODO：编辑这些注释，说明实现中任何有趣或值得注意的内容。
 */
#include "Sandpiles.h"
#include "GUI/SimpleTest.h"
using namespace std;

void dropSandOn(Grid<int>& world, int row, int col) {
    /* TODO：删除此行及其后三行，然后实现此函数。 */
    if(!world.inBounds(row, col))
    {
        return;
    }

    world[row][col]++;
    if(world[row][col] >= 4)
    {
        world[row][col] = 0;
        dropSandOn(world, row + 1, col);
        dropSandOn(world, row - 1, col);
        dropSandOn(world, row, col - 1);
        dropSandOn(world, row, col + 1);
    }
}






/* * * * * * 提供的测试用例 * * * * * */

PROVIDED_TEST("Dropping into an empty cell only changes that cell.") {
    /* 创建简单的源网格。 */
    Grid<int> before = {
        { 3, 3, 3 },
        { 3, 0, 3 },
        { 3, 3, 3 }
    };
    Grid<int> after = {
        { 3, 3, 3 },
        { 3, 1, 3 },
        { 3, 3, 3 }
    };

    dropSandOn(before, 1, 1);
    EXPECT_EQUAL(before, after); // 上述调用会更改“before”。
}

PROVIDED_TEST("Non-chaining topples work.") {
    /* 创建简单的源网格。 */
    Grid<int> before = {
        { 0, 0, 0 },
        { 1, 3, 1 },
        { 0, 2, 0 }
    };
    Grid<int> after = {
        { 0, 1, 0 },
        { 2, 0, 2 },
        { 0, 3, 0 }
    };

    dropSandOn(before, 1, 1);
    EXPECT_EQUAL(before, after); // 上述调用会更改“before”。
}

PROVIDED_TEST("Two topples chain.") {
    /* 创建简单的源网格。 */
    Grid<int> before = {
        { 0, 0, 0, 0 },
        { 0, 3, 3, 0 },
        { 0, 0, 0, 0 }
    };
    Grid<int> after = {
        { 0, 1, 1, 0 },
        { 1, 1, 0, 1 },
        { 0, 1, 1, 0 }
    };

    dropSandOn(before, 1, 1);
    EXPECT_EQUAL(before, after); // 上述调用会更改“before”。
}

/* TODO：需要在此测试套件中添加自己的测试。思考以下类型：
 * 我们在此测试了哪些输入；更重要的是，哪些输入*没有*测试。有些
 * 测试的一般规则：
 *
 *    1. 尝试极端情况。有哪些很大的情况需要检查？有哪些很小的情况？
 *
 *    2. 保持多样性。可能的输入很多，确保测试能够覆盖
 *       针对并非彼此简单变体的不同情况。
 *
 *    3. 尝试刁钻情况。不要只测试标准输入，还要测试一般人想不到的异常输入
 *       实际输入，但仍然完全合法。
 *
 * 祝测试顺利！
 */










