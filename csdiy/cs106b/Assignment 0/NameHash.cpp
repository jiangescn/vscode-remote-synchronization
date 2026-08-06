/**
 * 此程序为
 * 一个人的姓名。哈希是一个整数，
 * 从另一个对象通过数学方式推导得到。
 * 在此情况下，是一个字符串（名和姓）
 * 逐字符访问，并且哈希值
 * 由每个字符生成的数字逐步构建。
 * 虽然此函数不一定会生成
 * 唯一哈希值（不同名称可能哈希到
 * 相同值），其发生概率相对较低
 * 在约 400 名学生的班级中发生“碰撞”。
 *
 * 本学期后面会进一步学习哈希！
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"  // 用于 getLine
using namespace std;

/* nameHash 函数的原型。这样我们便可使用该函数
 * 在 main 中，然后在程序后面定义它。
 */
int nameHash(string first, string last);

int main() {
    string first = getLine("What is your first name? ");
    string last = getLine("What is your last name?  ");

    int hashValue = nameHash(first, last);

    cout << "The hash of your name is: " << hashValue << endl;
    return 0;
}

/* 这是真正计算哈希码的函数。我们将
 * 本学期后面会进一步讨论哈希函数的作用。目前，
 * 目前可将其视为一个打乱字符顺序的函数
 * 输入并生成一个数字。
 *
 * 对于数学基础更强的读者，此函数
 * 将输入名称中的每个字符视为 0 到 128 之间的数。
 * 然后将它们用作有限域上多项式的系数
 * F_p，其中 p 是一个大素数，并在以下位置计算该多项式：
 * 某个更小的素数 q。（CS106B 不要求你了解这一点，
 * 但我们觉得这可能很有趣！）
 */
int nameHash(string first, string last){
    /* 此哈希方案需要两个质数，一个大质数和一个小
     * 素数。选择这些数字是因为它们的乘积小于
     * 2^31 - kLargePrime - 1。
     */
    static const int kLargePrime = 16908799;
    static const int kSmallPrime = 127;

    int hashVal = 0;

    /* 先遍历名字中的所有字符，再遍历姓氏中的字符
     * 名称，并在每一步更新哈希值。
     */
    for (char ch: first + last) {
        /* 将输入字符转换为小写。以下字符的数值
         * 小写字母始终小于 127。
         */
        ch = tolower(ch);
        hashVal = (kSmallPrime * hashVal + ch) % kLargePrime;
    }
    return hashVal;
}
