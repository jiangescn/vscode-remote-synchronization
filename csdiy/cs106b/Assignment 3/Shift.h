#ifndef Shift_Included
#define Shift_Included

#include <string>
#include <ostream>

/* 表示星期几的类型。 */
enum class Day {
    SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
};

/* 表示工作日班次的类型。为简化起见，我们假定
 * 每个班次只发生在特定日历日，因此不能让某个班次
 * 从周一 10:00PM 到周二 2:00AM。这只是为了让你的生活稍微
 * 在编写代码过程中更容易——它并不表示所有班次
 * 在现实中这样对齐得更整齐。
 */
struct Shift {
    Day day;
    int startHour; // 包含端点。
    int endHour;   // 不含上界。可以为 24，表示“一直到午夜”
    int value;     // 此班次产生的价值。
};

/* 给定两个班次，报告它们是否相互重叠。 */
bool overlapsWith(const Shift& one, const Shift& two);

/* 给定一个班次，返回其长度或价值。这些函数仅为方便而提供。 */
int lengthOf(const Shift& shift);
int valueOf(const Shift& shift);


/* * * * * 你不需要阅读以下任何内容，但感兴趣的话可以继续！* * * * */


/* 这些运算符使在 Map 和 HashMap 中存储 Shift 成为可能（如果需要）
 * 你希望执行的操作。
 */
bool operator<  (const Shift& lhs, const Shift& rhs);
bool operator== (const Shift& lhs, const Shift& rhs);
int  hashCode   (const Shift& shift);

/* 这些运算符使输出 Shift 和 Day 成为可能（如果需要）
 * 你希望执行的操作。
 */
std::ostream& operator<< (std::ostream& out, Day day);
std::ostream& operator<< (std::ostream& out, const Shift& shift);

#endif
