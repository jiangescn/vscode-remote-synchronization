/* 文件：PlayingFair.cpp
 *
 * TODO：编辑这些注释，说明实现中任何有趣或值得注意的内容。
 */
#include "PlayingFair.h"
#include "GUI/SimpleTest.h"
#include "error.h"
using namespace std;

string aSequenceOfOrder(int n) {
    /* TODO：删除此行及接下来的两行，然后实现此函数。 */
    if (n < 0)
    {
        error("序列的阶数不能为负数。");
    }
    if (n == 0)
    {
        return "A";
    }

    return aSequenceOfOrder(n - 1) + bSequenceOfOrder(n - 1);
}

string bSequenceOfOrder(int n) {
    /* TODO：删除此行及接下来的两行，然后实现此函数。 */
    if (n < 0)
    {
        error("序列的阶数不能为负数。");
    }
    if (n == 0)
    {
        return "B";
    }
    return bSequenceOfOrder(n - 1) + aSequenceOfOrder(n - 1);
}






/* * * * * * 提供的测试用例 * * * * * */

PROVIDED_TEST("Sequences of order 3 are correct.") {
    /* 一些非常基本的检查。 */
    EXPECT_EQUAL(aSequenceOfOrder(3), "ABBABAAB");
    EXPECT_EQUAL(bSequenceOfOrder(3), "BAABABBA");
}

PROVIDED_TEST("Only characters should be As and Bs.") {
    for (int i = 0; i < 10; i++) {
        for (char ch: aSequenceOfOrder(i)) {
            EXPECT(ch == 'A' || ch == 'B');
        }
    }
}

PROVIDED_TEST("A-sequence of positive order should have equal As and Bs.") {
    /* 排除 0 阶序列，它只有一个字符。 */
    for (int i = 1; i < 10; i++) {
        int as = 0;
        int bs = 0;
        for (char ch: aSequenceOfOrder(i)) {
            if (ch == 'A') as++;
            else bs++;
        }

        EXPECT_EQUAL(as, bs);
    }
}

PROVIDED_TEST("Triggers error on negative inputs.") {
    /* EXPECT_ERROR 宏期望给定表达式调用 error()。请记住
     * 需要防范无效输入。
     */
    EXPECT_ERROR(aSequenceOfOrder(-137));
    EXPECT_ERROR(bSequenceOfOrder(-137));
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








