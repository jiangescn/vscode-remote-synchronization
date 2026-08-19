#include "WhatAreYouDoing.h"
#include "strlib.h"
using namespace std;

/* TODO：阅读 WhatAreYouDoing.h 中的注释，了解此函数需要执行什么，然后
 * 删除此注释。
 *
 * 不要忘记 WhatAreYouDoing.h 中定义的 tokenize 函数；你几乎
 * 肯定希望使用它。
 */

string Vector_to_string(Vector<string>& s)
{
    string ans = "";
    for (auto it : s)
    {
        ans += it;
    }
    return ans;
}


void dfs(Set<string> &ans, Vector<string> token, int deep)
{
    if(deep == token.size())
    {
        ans.add(Vector_to_string(token));
        return;
    }

    dfs(ans, token, deep + 1);
    if(!isalpha(token[deep][0]))
    {
        return;
    }

    token[deep] = toLowerCase(token[deep]);
    dfs(ans, token, deep + 1);
}


Set<string> allEmphasesOf(const string& sentence) {
    /* TODO：删除此行及下一行，然后实现此函数。 */
    Vector<string> token = tokenize(sentence);
    Set<string> ans;

    for (string &it : token)
    {
        it = toUpperCase(it);
    }
    dfs(ans, token, 0);
    return ans;
}



/* * * * * * 测试用例 * * * * * */
#include "GUI/SimpleTest.h"

/* TODO：在此添加你自己的测试。方法你已经熟悉了——寻找边界情况，并考虑
 * 极小、极大的情况等。
 */














/* * * * * * 此处以下为起始文件中的测试用例。* * * * * */

PROVIDED_TEST("Enumerates all options in a simple case.") {
    Set<string> expected = {
        "hello",
        "HELLO",
    };

    EXPECT_EQUAL(allEmphasesOf("Hello"), expected);
}

PROVIDED_TEST("Each option has the right length.") {
    string sentence = "Hello, world!";
    for (string option: allEmphasesOf(sentence)) {
        EXPECT_EQUAL(option.length(), sentence.length());
    }
}

PROVIDED_TEST("Enumerates all options in a more typical case.") {
    Set<string> expected = {
        "you are?",
        "you ARE?",
        "YOU are?",
        "YOU ARE?"
    };

    EXPECT_EQUAL(allEmphasesOf("You Are?"), expected);
}

PROVIDED_TEST("Stress Test: Recursion only branches on words (should take under a second)") {
    /* 我们正在生成由 50 个 * 字符组成的字符串。它会被标记化
     * 分成五十个独立的星号。星号无论是否大写都相同——不存在
     * 不存在“大写”或“小写”星号。因此，你的代码应当
     * 不要尝试生成两个句子版本，一个将星号大写，另一个
     * 若不这样做，因为两个版本最终会相同，而计算
     * 两个选项都会显著增加运行时间。
     *
     * 作为参考，如果确实尝试让递归分支，并检查以下两种情况分别会发生什么：
     * 若将星号大写；否则会尝试探索 2^50 种不同的可能
     * 各种大小写形式。共有 1,125,899,906,842,624 个选项，即使每秒处理十亿个
     * 若每秒生成这么多个，生成全部排列将需要两年多！当然，
     * 那全是无用工作，因为此句子只有一种大写方式，并且
     * 就是保持原样。
     *
     * 如果运行此测试时代码卡住，很可能意味着代码正在
     * 尝试枚举所有这些选项。看看能否编辑代码，使得如果
     * 如果给定的是非单词标记，只需保持原样，不做任何更改。
     */
    string punctuation(50, '*'); // 50 个 *

    /* 唯一的强调项是它本身。 */
    Set<string> expected = {
        punctuation
    };

    EXPECT_EQUAL(allEmphasesOf(punctuation), expected);
}

PROVIDED_TEST("Stress test: Generates each option once (should take at most a few seconds)") {
    /* 这句话有 13 个单词。因此它共有 2^13 = 8192 种可能的强调方式
     * 其中的单词数量很大，但还没有大到计算机无法处理
     * 如果它恰好生成每种强调形式一次。
     *
     * 另一方面，如果代码尝试多次生成相同强调形式，
     * 此测试可能需要非常非常长的时间，甚至看起来像是卡死
     * 向上。
     *
     * 如果代码卡在此测试中，请跟踪代码并确认不会
     * 多次生成相同强调形式。请检查是否存在例如以下情况
     * 遍历输入句子中的每个令牌，并决定哪一个要大写
     * 下一个。这里的递归更遵循包含/排除模式（更像
     * 更像子集和组合），而不是“下一个是谁？”类型模式（更像
     * 排列）。
     */
    string yeats = "Turing and turning in a widening gyre / the falcon cannot hear the falconer.";
    EXPECT_EQUAL(allEmphasesOf(yeats).size(), 8192);
}
