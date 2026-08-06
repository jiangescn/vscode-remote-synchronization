/* 文件：OnlyConnect.cpp
 *
 * TODO：编辑这些注释，说明实现中任何有趣或值得注意的内容。
 *
 * TODO：编辑这些注释，给你的助教留一道谜题！
 */
#include "OnlyConnect.h"
#include "GUI/SimpleTest.h"
using namespace std;


bool isV(char ch)
{
    ch = toUpperCase(ch);
    return ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U';
}

string onlyConnectize(string phrase) {
    /* TODO：下面几行仅用于确保你不会收到编译器警告消息
     * 当此函数尚未实现时。删除这些行，然后实现此函数。
     */
    if(phrase.empty())
    {
        return "";
    }

    char first = phrase[0];
    string remain = onlyConnectize(phrase.substr(1));

    if(isalpha(first) && !isV(first))
    {
        return char(toupper(first)) + remain;
    }
    return remain;
}






/* * * * * * 提供的测试用例 * * * * * */

PROVIDED_TEST("Converts lower-case to upper-case.") {
    EXPECT_EQUAL(onlyConnectize("lowercase"), "LWRCS");
    EXPECT_EQUAL(onlyConnectize("uppercase"), "PPRCS");
}

PROVIDED_TEST("Handles non-letter characters properly.") {
    EXPECT_EQUAL(onlyConnectize("2.718281828459045"), "");
    EXPECT_EQUAL(onlyConnectize("'Hi, Mom!'"), "HMM");
}

PROVIDED_TEST("Handles single-character inputs.") {
    EXPECT_EQUAL(onlyConnectize("A"), "");
    EXPECT_EQUAL(onlyConnectize("+"), "");
    EXPECT_EQUAL(onlyConnectize("Q"), "Q");
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






