#include "HumanPyramids.h"
using namespace std;

/* TODO：有关此函数应执行什么操作的更多信息，请参阅 HumanPyramids.h。
 * 然后删除此注释。
 */
double weightOnBackOf(int row, int col, int pyramidHeight) {
    /* TODO：删除接下来的几行并实现此函数。 */
    (void) row;
    (void) col;
    (void) pyramidHeight;
    return 0;
}






/* * * * * * 测试用例 * * * * * */
#include "GUI/SimpleTest.h"

/* TODO：在此添加你自己的测试。方法你已经熟悉了——寻找边界情况，并考虑
 * 极小、极大的情况等。
 */














/* * * * * * 此处以下为起始文件中的测试用例。* * * * * */

PROVIDED_TEST("Check Person E from the handout.") {
    /* 人员 E 位于第 2 行、第 1 列。 */
    EXPECT_EQUAL(weightOnBackOf(2, 1, 5), 240);
}

PROVIDED_TEST("Function reports errors in invalid cases.") {
    EXPECT_ERROR(weightOnBackOf(-1, 0, 10));
    EXPECT_ERROR(weightOnBackOf(10, 10, 5));
    EXPECT_ERROR(weightOnBackOf(-1, 10, 20));
}

PROVIDED_TEST("Stress test: Memoization is implemented (should take under a second)") {
    /* TODO：是的，我们要求你修改此测试用例！删除
     * 紧接在此行后的那一行——以 SHOW_ERROR 开头的行——一旦
     * 实现记忆化后，用它测试实现是否正确。
     */
    SHOW_ERROR("This test is configured to always fail until you delete this line from\n         HumanPyramids.cpp. Once you have implemented memoization and want\n         to check whether it works correctly, remove the indicated line.");

    /* 不要删除此处以下任何内容。:-) */

    /* 如果没有实现记忆化，此过程将需要很长时间。
     * 所需时间堪比“宇宙热寂”。:-)
     *
     * 如果你实现了记忆化但此测试用例仍然卡住，请确认
     * 确保在递归函数（而不是包装函数）中，你的递归
     * 调用的是新的递归函数，而不是返回包装器。如果你
     * 再次调用包装器时，会得到全新的记忆化表，而不是
     * 保留递归探索过程中正在构建的那个，以及
     * 效果将如同完全没有实现记忆化。
     */
    EXPECT(weightOnBackOf(100, 50, 200) >= 10000);
}

/* TODO：在此添加你自己的测试。方法你已经熟悉了——寻找边界情况，并考虑
 * 极小、极大的情况等。
 */
