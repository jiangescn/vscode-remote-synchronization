#include "Permutations.h"
using namespace std;

/* 返回给定输入字符串的所有排列。
 *
 * 注意：这里提供的初始实现不正确。你需要
 * 使用调试器定位错误，然后回答一些有关
 * 说明此代码为什么错误。请记住，该错误完全由
 * 仅增加一个额外字符；你不需要进行任何重大
 * 需要进行修改以修复此函数。
 *
 * 这里是否应使用 const 引用传递？可能应该。这本身
 * 本身不是错误，但与这里出错的原因有关。
 */
Set<string> permutationsRec(string str, string chosen) {
    /* 基本情况：如果没有剩余字符需要考虑，则
     * 唯一可能的排列就是仅由
     * 我们已经承诺的内容。
     */
    if (str == "") {
        return { chosen };
    }
    /* 递归情况：必须有某个字符作为排列中的下一个字符。
     * 应选择哪一个？让我们尝试所有可能选项并查看
     * 查找。
     */
    else {
        /* 保存我们找到的所有排列。 */
        Set<string> result;
        for (int i = 0; i < str.size(); i++) {
            /* 通过获取以下部分，组成包含所有剩余字母的新字符串：
             * 直到但不包括当前字符，然后是之后的所有内容
             * 当前字符。
             */
            char ch = str[i];
            string remaining = str.substr(0, i) + str.substr(i + 1);

            /* 找出使用此选择可以生成的所有排列，并将其添加到
             * 结果。
             */
            Set<string> thisOption = permutationsRec(remaining, chosen += ch);
            result += thisOption;
        }

        /* 现在已尝试所有选项，因此返回所得结果。 */
        return result;
    }
}

Set<string> permutationsOf(const string& str) {
    return permutationsRec(str, "");
}
