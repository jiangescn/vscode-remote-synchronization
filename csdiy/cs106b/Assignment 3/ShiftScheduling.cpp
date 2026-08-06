#include "ShiftScheduling.h"
using namespace std;

/* TODO：有关此函数应执行什么操作的更多信息，请参阅 ShiftScheduling.h。
 * 然后删除此注释，并替换为你自己的注释。
 */
Set<Shift> highestValueScheduleFor(const Set<Shift>& shifts, int maxHours) {
    /* TODO：删除接下来的几行并实现此函数。 */
    (void) shifts;
    (void) maxHours;
    return {};
}



/* * * * * * 测试用例 * * * * * */
#include "GUI/SimpleTest.h"

/* TODO：在此添加你自己的测试。方法你已经熟悉了——寻找边界情况，并考虑
 * 极小、极大的情况等。
 */














/* * * * * * 此处以下为起始文件中的测试用例。* * * * * */
#include "vector.h"
#include "error.h"

/* 这个实用工具函数允许你调用 highestValueScheduleFor，并传入
 * 使用班次的 Vector 而不是 Set。这会使测试更容易一些。
 * 除这些测试用例外，你应不需要此函数。
 */
Set<Shift> asSet(const Vector<Shift>& shifts) {
    Set<Shift> result;
    for (Shift s: shifts) {
        result += s;
    }
    return result;
}

PROVIDED_TEST("Pick only shift if you have time for it.") {
    Set<Shift> shifts = {
        { Day::MONDAY, 9, 17, 1000 },  // 周一，9AM - 5PM，值为 1000
    };

    EXPECT_EQUAL(highestValueScheduleFor(shifts, 24).size(), 1);
    EXPECT_EQUAL(highestValueScheduleFor(shifts, 24), shifts);
}

PROVIDED_TEST("Don't pick only shift if ou don't have time for it.") {
    Set<Shift> shifts = {
        { Day::MONDAY, 9, 17, 1000 },  // 周一，9AM - 5PM，值为 1000
    };

    EXPECT_EQUAL(highestValueScheduleFor(shifts, 3).size(), 0);
}

PROVIDED_TEST("Don't pick overlapping shifts.") {
    Vector<Shift> shifts = {
        { Day::MONDAY, 9, 17, 1000 },  // 周一，上午 9 点 - 下午 5 点，价值为 1000
        { Day::MONDAY, 8, 18, 2000 },  // 周一，上午 10 点 - 下午 6 点，价值为 2000
    };

    EXPECT_EQUAL(highestValueScheduleFor(asSet(shifts), 100), { shifts[1] });
}

PROVIDED_TEST("Doesn't always use highest-value shift.") {
    Vector<Shift> shifts = {
        { Day::MONDAY,    10, 20, 1000 }, // 10 小时班次，值为 1000
        { Day::TUESDAY,   10, 15,  500 }, //  5 小时班次，值为 500
        { Day::WEDNESDAY, 10, 16,  501 }, //  6 小时班次，值为 501
    };

    /* 正确策略是放弃价值最高的班次，改选两个
     * 更短的班次。
     */
    auto schedule = highestValueScheduleFor(asSet(shifts), 11);

    EXPECT_EQUAL(schedule, { shifts[1], shifts[2] });
}

PROVIDED_TEST("Doesn't always use the shift with the highest value per unit time.") {
    Vector<Shift> shifts = {
        { Day::MONDAY,    10, 17, 21 }, //  7 小时班次，值为 21（每小时 $3）
        { Day::TUESDAY,   10, 16, 12 }, //  6 小时班次，值为 12（每小时 2 美元）
        { Day::WEDNESDAY, 10, 16, 12 }, //  6 小时班次，值为 12（每小时 2 美元）
    };

    /* 如果有 12 小时，正确策略是选择两个六小时班次
     * 总价值为 $24。选择单位时间价值最高的班次
     * 时间（七小时班次）只产生 $21 的价值。
     */
    auto schedule = highestValueScheduleFor(asSet(shifts), 12);

    EXPECT_EQUAL(schedule, { shifts[1], shifts[2] });
}

PROVIDED_TEST("Passes the example from the assignment description.") {
    Vector<Shift> shifts = {
        { Day::MONDAY,     8, 12, 27 },  // 周一 上午 8 点 - 中午 12 点，价值 27 *
        { Day::MONDAY,    12, 16, 28 },  // 周一 中午 12 点 - 下午 4 点，价值 28 *
        { Day::MONDAY,    16, 20, 25 },  // 周一 下午 4 点 - 8 点，价值 25 *
        { Day::MONDAY,     8, 14, 39 },  // 周一 08:00-14:00，值 39
        { Day::MONDAY,    14, 20, 31 },  // 周一 14:00-20:00，值 31
        { Day::TUESDAY,    8, 12,  7 },  // 周二 08:00-12:00，值 7
        { Day::TUESDAY,   12, 16,  7 },  // 周二 12:00-16:00，值 7
        { Day::TUESDAY,   16, 20, 11 },  // 周二 16:00-20:00，值 11
        { Day::TUESDAY,    8, 14, 10 },  // 周二 08:00-14:00，值 10
        { Day::TUESDAY,   14, 20,  8 },  // 周二 14:00-20:00，值 8
        { Day::WEDNESDAY,  8, 12, 10 },  // 周三 08:00-12:00，值 10
        { Day::WEDNESDAY, 12, 16, 11 },  // 周三 12:00-16:00，值 11
        { Day::WEDNESDAY, 16, 20, 13 },  // 周三 16:00-20:00，值 13
        { Day::WEDNESDAY,  8, 14, 19 },  // 周三 08:00-14:00，值 19
        { Day::WEDNESDAY, 14, 20, 25 },  // 周三 下午 2 点 - 晚上 8 点，价值 25 *
    };

    /* 取回解。 */
    Set<Shift> computedSolution = highestValueScheduleFor(asSet(shifts), 20);

    /* 组成正确答案，即带星号的条目。 */
    Set<Shift> actualSolution = {
        shifts[0], shifts[1], shifts[2], shifts[14]
    };

    EXPECT_EQUAL(computedSolution, actualSolution);
}

PROVIDED_TEST("Handles no shifts.") {
    EXPECT_EQUAL(highestValueScheduleFor({}, 137).size(), 0);
}

PROVIDED_TEST("Reports an error with negative hours.") {
    /* 来自作业说明。 */
    Vector<Shift> shifts = {
        { Day::MONDAY,     8, 12, 27 },  // 周一  8AM - 12PM，值为 27
        { Day::MONDAY,    12, 16, 28 },  // 周一 12PM -  4PM，值为 28
        { Day::MONDAY,    16, 20, 25 },  // 周一  4PM -  8PM，值为 25
        { Day::MONDAY,     8, 14, 39 },  // 周一 08:00-14:00，值 39
        { Day::MONDAY,    14, 20, 31 },  // 周一 14:00-20:00，值 31
        { Day::TUESDAY,    8, 12,  7 },  // 周二 08:00-12:00，值 7
        { Day::TUESDAY,   12, 16,  7 },  // 周二 12:00-16:00，值 7
        { Day::TUESDAY,   16, 20, 11 },  // 周二 16:00-20:00，值 11
        { Day::TUESDAY,    8, 14, 10 },  // 周二 08:00-14:00，值 10
        { Day::TUESDAY,   14, 20,  8 },  // 周二 14:00-20:00，值 8
        { Day::WEDNESDAY,  8, 12, 10 },  // 周三 08:00-12:00，值 10
        { Day::WEDNESDAY, 12, 16, 11 },  // 周三 12:00-16:00，值 11
        { Day::WEDNESDAY, 16, 20, 13 },  // 周三 16:00-20:00，值 13
        { Day::WEDNESDAY,  8, 14, 19 },  // 周三 08:00-14:00，值 19
        { Day::WEDNESDAY, 14, 20, 25 },  // 周三  2PM -  8PM，值为 25
    };

    /* 应当报错。 */
    EXPECT_ERROR(highestValueScheduleFor(asSet(shifts), -1));

    /* 即使没有班次，仍然应报错。 */
    EXPECT_ERROR(highestValueScheduleFor({}, -1));
}

PROVIDED_TEST("Handles zero free hours.") {
    /* 来自作业说明。 */
    Vector<Shift> shifts = {
        { Day::MONDAY,     8, 12, 27 },  // 周一  8AM - 12PM，值为 27
        { Day::MONDAY,    12, 16, 28 },  // 周一 12PM -  4PM，值为 28
        { Day::MONDAY,    16, 20, 25 },  // 周一  4PM -  8PM，值为 25
        { Day::MONDAY,     8, 14, 39 },  // 周一 08:00-14:00，值 39
        { Day::MONDAY,    14, 20, 31 },  // 周一 14:00-20:00，值 31
        { Day::TUESDAY,    8, 12,  7 },  // 周二 08:00-12:00，值 7
        { Day::TUESDAY,   12, 16,  7 },  // 周二 12:00-16:00，值 7
        { Day::TUESDAY,   16, 20, 11 },  // 周二 16:00-20:00，值 11
        { Day::TUESDAY,    8, 14, 10 },  // 周二 08:00-14:00，值 10
        { Day::TUESDAY,   14, 20,  8 },  // 周二 14:00-20:00，值 8
        { Day::WEDNESDAY,  8, 12, 10 },  // 周三 08:00-12:00，值 10
        { Day::WEDNESDAY, 12, 16, 11 },  // 周三 12:00-16:00，值 11
        { Day::WEDNESDAY, 16, 20, 13 },  // 周三 16:00-20:00，值 13
        { Day::WEDNESDAY,  8, 14, 19 },  // 周三 08:00-14:00，值 19
        { Day::WEDNESDAY, 14, 20, 25 },  // 周三  2PM -  8PM，值为 25
    };

    /* 时间为零不应报错——这表示我们不选择任何内容。 */
    EXPECT_EQUAL(highestValueScheduleFor(asSet(shifts), 0).size(), 0);
}

PROVIDED_TEST("Stress test: Don't generate shift combinations with overlapping shifts.") {
    /* 所有这些班次都相互重叠。如果尝试生成所有组合
     * 这些班次，并且只在最后检查其是否有效，你将会
     * 检查约 2^100 ≈ 10^30 种班次组合，这将耗费极长时间，以至于
     * 在完成之前太阳都已经熄灭了。
     *
     * 相反，在遍历决策树并构建班次时，
     * 确保不要包含任何明显与已有内容冲突的班次
     * 之前选择的。
     */
    Set<Shift> trickySet;
    for (int i = 0; i < 100; i++) {
        trickySet += Shift{ Day::MONDAY, 1, 2, i };
    }
    EXPECT_EQUAL(trickySet.size(), 100);

    auto result = highestValueScheduleFor(trickySet, 1);
    EXPECT_EQUAL(result.size(), 1);
}

PROVIDED_TEST("Stress test: Don't generate shift combinations that exceed time limits.") {
    /* 这是一个每周每小时对应一个班次的集合。你的员工恰好有
     * 一个小时空闲。如果尝试这些班次的所有可能组合而忽略时间
     * 在这些约束下，需要检查 2^100 = 10^30 种组合，这将
     * 处理时间将超过已知宇宙的寿命。
     *
     * 相反，在探索决策树以生成班次组合时，
     * 确保不要添加会超过时间限制的班次。
     */
    Set<Shift> trickySet;
    for (Day day: { Day::SUNDAY,
                    Day::MONDAY,
                    Day::TUESDAY,
                    Day::WEDNESDAY,
                    Day::THURSDAY,
                    Day::FRIDAY,
                    Day::SATURDAY}) {
        for (int start = 0; start < 24; start++) {
            trickySet += Shift{ day, start, start + 1, 10 };
        }
    }
    EXPECT_EQUAL(trickySet.size(), 7 * 24);

    auto result = highestValueScheduleFor(trickySet, 1);
    EXPECT_EQUAL(result.size(), 1);
}

PROVIDED_TEST("Stress test: Can handle a decent number of shifts (should take at most 10-15 seconds)") {
    /* 可用班次。 */
    Vector<Shift> shifts = {
        { Day::SUNDAY,  8, 14, 12 },
        { Day::SUNDAY, 12, 18, 36 },

        { Day::MONDAY,  8, 12, 44 },
        { Day::MONDAY, 12, 16, 32 },
        { Day::MONDAY, 16, 20,  0 },
        { Day::MONDAY,  8, 16, 16 },
        { Day::MONDAY, 12, 20, 22 },

        { Day::TUESDAY,  8, 12, 48 },
        { Day::TUESDAY, 12, 16, 20 },
        { Day::TUESDAY, 16, 20, 24 },
        { Day::TUESDAY,  8, 16, 24 },
        { Day::TUESDAY, 12, 20, 80 },

        { Day::WEDNESDAY,  8, 12, 20 },
        { Day::WEDNESDAY, 12, 16,  8 },
        { Day::WEDNESDAY, 16, 20,  8 },
        { Day::WEDNESDAY,  8, 16, 40 },
        { Day::WEDNESDAY, 12, 20, 16 },

        { Day::THURSDAY,  8, 12, 40 },
        { Day::THURSDAY, 12, 16,  0 },
        { Day::THURSDAY, 16, 20, 24 },
        { Day::THURSDAY,  8, 16, 56 },
        { Day::THURSDAY, 12, 20, 32 },

        { Day::FRIDAY,  8, 12,  4 },
        { Day::FRIDAY, 12, 16,  8 },
        { Day::FRIDAY, 16, 20, 40 },
        { Day::FRIDAY,  8, 16, 72 },
        { Day::FRIDAY, 12, 20, 40 },

        { Day::SATURDAY,  8, 14, 18 },
        { Day::SATURDAY, 12, 18, 66 },
    };

    auto answer = highestValueScheduleFor(asSet(shifts), 30);
    EXPECT_EQUAL(answer, { shifts[2], shifts[7], shifts[11], shifts[17], shifts[24], shifts[28] });
}
