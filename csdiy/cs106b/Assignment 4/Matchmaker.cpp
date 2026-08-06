#include "Matchmaker.h"
using namespace std;

bool hasPerfectMatching(const Map<string, Set<string>>& possibleLinks, Set<Pair>& matching) {
    /* TODO：删除此注释和剩余这些行，然后实现此函数。 */
    (void) possibleLinks;
    (void) matching;
    return false;
}

Set<Pair> maximumWeightMatching(const Map<string, Map<string, int>>& possibleLinks) {
    /* TODO：删除此注释和剩余这些行，然后实现此函数。 */
    (void) possibleLinks;
    return { };
}

/* * * * * 此处以下为测试用例 * * * * */

namespace {
    /* 将三元组列表转换为世界的实用工具。 */
    struct WeightedLink {
        string from;
        string to;
        int cost;
    };
    Map<string, Map<string, int>> fromWeightedLinks(const Vector<WeightedLink>& links) {
        Map<string, Map<string, int>> result;
        for (const auto& link: links) {
            result[link.from][link.to] = link.cost;
            result[link.to][link.from] = link.cost;
        }
        return result;
    }

    /* 将配对转换到世界坐标。 */
    Map<string, Set<string>> fromLinks(const Vector<Pair>& pairs) {
        Map<string, Set<string>> result;
        for (const auto& link: pairs) {
            result[link.first()].add(link.second());
            result[link.second()].add(link.first());
        }
        return result;
    }

    /* 检查一组配对是否构成完美匹配。 */
    bool isPerfectMatching(const Map<string, Set<string>>& possibleLinks,
                           const Set<Pair>& matching) {
        /* 需要检查
         *
         * 1. 每一对确实是可能的连接，
         * 2. 每个人恰好出现在一对中。
         */
        Set<string> used;
        for (Pair p: matching) {
            /* 这些人甚至属于该群体吗？ */
            if (!possibleLinks.containsKey(p.first())) return false;
            if (!possibleLinks.containsKey(p.second())) return false;

            /* 如果这些人在该群组中，他们是否相连？ */
            if (!possibleLinks[p.first()].contains(p.second()) ||
                !possibleLinks[p.second()].contains(p.first())) {
                return false;
            }

            /* 我们以前见过它们吗？ */
            if (used.contains(p.first()) || used.contains(p.second())) {
                return false;
            }

            /* 同时添加二者。 */
            used += p.first();
            used += p.second();
        }

        /* 确认所有人都在其中。 */
        return used.size() == possibleLinks.size();
    }
}

#include "GUI/SimpleTest.h"

PROVIDED_TEST("hasPerfectMatching works on a world with just one person.") {
    /* 世界中只有一个人 A，没有其他人。真可怜。:-(
     *
     *                 A
     *
     * 这里不存在完美匹配。
     */

    Set<Pair> unused;
    EXPECT(!hasPerfectMatching({ { "A", {} } }, unused));
}

PROVIDED_TEST("hasPerfectMatching works on an empty set of people.") {
    /* 实际上存在完美匹配——不含任何连接的集合满足
     * 要求。
     */
    Set<Pair> unused;
    EXPECT(hasPerfectMatching({}, unused));
}

PROVIDED_TEST("hasPerfectMatching works on a world with two linked people.") {
    /* 这个世界由 A 和 B 两个人组成。应当存在完美匹配。
     *
     *               A -- B
     *
     * 匹配为 {A, B}
     */
    auto links = fromLinks({
        { "A", "B" }
    });

    Set<Pair> unused;
    EXPECT(hasPerfectMatching(links, unused));
}

PROVIDED_TEST("hasPerfectMatching works on a world with two linked people, and produces output.") {
    /* 这个世界由 A 和 B 两个人组成。应当存在完美匹配。
     *
     *               A -- B
     *
     * 匹配为 {A, B}
     */
    auto links = fromLinks({
        { "A", "B" }
    });

    Set<Pair> expected = {
        { "A", "B" }
    };

    Set<Pair> matching;
    EXPECT(hasPerfectMatching(links, matching));
    EXPECT_EQUAL(matching, expected);
}

PROVIDED_TEST("hasPerfectMatching works on a triangle of people.") {
    /* 当前世界如下：
     *
     *               A --- B
     *                \   /
     *                 \ /
     *                  C
     *
     * 很遗憾，这里不存在完美匹配。
     */
    auto links = fromLinks({
        { "A", "B" },
        { "B", "C" },
        { "C", "A" }
    });

    Set<Pair> unused;
    EXPECT(!hasPerfectMatching(links, unused));
}

PROVIDED_TEST("hasPerfectMatching works on a square of people.") {
    /* 当前世界如下：
     *
     *               A --- B
     *               |     |
     *               |     |
     *               D --- C
     *
     * 这里有两个不同的完美匹配：AB / CD 和 AD/BD。
     * 两种方式都可以。
     */
    auto links = fromLinks({
        { "A", "B" },
        { "B", "C" },
        { "C", "D" },
        { "D", "A" }
    });

    Set<Pair> unused;
    EXPECT(hasPerfectMatching(links, unused));
}

PROVIDED_TEST("hasPerfectMatching works on a square of people, and produces output.") {
    /* 当前世界如下：
     *
     *               A --- B
     *               |     |
     *               |     |
     *               C --- D
     *
     * 这里有两个不同的完美匹配：AB / CD 和 AC/BC。
     * 两种方式都可以。
     */
    auto links = fromLinks({
        { "A", "B" },
        { "B", "C" },
        { "C", "D" },
        { "D", "A" }
    });

    Set<Pair> matching;
    EXPECT(hasPerfectMatching(links, matching));
    EXPECT(isPerfectMatching(links, matching));
}

PROVIDED_TEST("hasPerfectMatching works on a pentagon of people.") {
    /* 当前世界如下：
     *
     *               A --- B
     *             /       |
     *            E        |
     *             \       |
     *               D --- C
     *
     * 这里不存在完美匹配，因为该环的长度为奇数
     * 长度。
     */
    auto links = fromLinks({
        { "A", "B" },
        { "B", "C" },
        { "C", "D" },
        { "D", "E" },
        { "E", "A" }
    });

    Set<Pair> unused;
    EXPECT(!hasPerfectMatching(links, unused));
}

PROVIDED_TEST("hasPerfectMatching works on a line of six people.") {
    /* 由于 Map 和 Set 在内部按排序顺序存储条目，因此该顺序
     * 做决策时遍历人员的顺序会影响结果
     * 结果会受这些人员姓名顺序影响。此测试使用类似如下的分组：
     * 此测试尝试人员姓名的所有可能排列：
     *
     *
     *
     *        * -- * -- * -- * -- * -- *
     *
     *
     *
     * 这六个项目共有 6! = 720 种可能的排列
     * 人员。如果代码能够针对所有这些情况正确解决问题，
     * 若这些排列都能通过，很可能说明你正确跟踪了
     * 每一步谁与谁配对。另一方面，如果代码出现
     * 若这里出现问题，可能表示标记配对状态的方式存在错误：
     * 谁已配对、谁未配对。
     */
    Vector<string> people = { "A", "B", "C", "D", "E", "F" };
    do {
        Map<string, Set<string>> links = fromLinks({
            { people[0], people[1] },
            { people[1], people[2] },
            { people[2], people[3] },
            { people[3], people[4] },
            { people[4], people[5] }
        });

        Set<Pair> matching;
        EXPECT(hasPerfectMatching(links, matching));
        EXPECT(isPerfectMatching(links, matching));
    } while (next_permutation(people.begin(), people.end()));
}

PROVIDED_TEST("hasPerfectMatching works on a more complex negative example.") {
    /* 由于 Map 和 Set 在内部按排序顺序存储条目，因此该顺序
     * 做决策时遍历人员的顺序会影响结果
     * 结果会受这些人员姓名顺序影响。此测试使用类似如下的分组：
     * 此测试尝试人员姓名的所有可能排列：
     *
     *
     *         *        *
     *          \      /
     *           * -- *
     *          /      \
     *         *        *
     *
     * 这六个项目共有 6! = 720 种可能的排列
     * 人员。如果代码能够针对所有这些情况正确解决问题，
     * 若这些排列都能通过，很可能说明你正确跟踪了
     * 每一步谁与谁配对。另一方面，如果代码出现
     * 若这里出现问题，可能表示标记配对状态的方式存在错误：
     * 谁已配对、谁未配对。
     */
    Vector<string> people = { "A", "B", "C", "D", "E", "F" };
    do {
        Map<string, Set<string>> links = fromLinks({
            { people[0], people[2] },
            { people[1], people[2] },
            { people[2], people[3] },
            { people[3], people[4] },
            { people[3], people[5] },
        });

        Set<Pair> matching;
        EXPECT(!hasPerfectMatching(links, matching));
    } while (next_permutation(people.begin(), people.end()));
}

PROVIDED_TEST("hasPerfectMatching works on a more complex positive example.") {
    /* 由于 Map 和 Set 在内部按排序顺序存储条目，因此该顺序
     * 做决策时遍历人员的顺序会影响结果
     * 结果会受这些人员姓名顺序影响。此测试使用类似如下的分组：
     * 此测试尝试人员姓名的所有可能排列：
     *
     *               *
     *               |
     *               *
     *              / \
     *             *---*
     *            /     \
     *           *       *
     *
     * 这些项的排列顺序共有 6! = 720 种可能
     * 人员。如果代码能够针对所有这些情况正确解决问题，
     * 若这些排列都能通过，很可能说明你正确跟踪了
     * 每一步谁与谁配对。另一方面，如果代码出现
     * 若这里出现问题，可能表示标记配对状态的方式存在错误：
     * 谁已配对、谁未配对。
     */
    Vector<string> people = { "A", "B", "C", "D", "E", "F" };
    do {
        Map<string, Set<string>> links = fromLinks({
            { people[0], people[1] },
            { people[1], people[2] },
            { people[2], people[3] },
            { people[3], people[1] },
            { people[2], people[4] },
            { people[3], people[5] },
        });

        Set<Pair> matching;
        EXPECT(hasPerfectMatching(links, matching));
        EXPECT(isPerfectMatching(links, matching));
    } while (next_permutation(people.begin(), people.end()));
}

PROVIDED_TEST("hasPerfectMatching works on a caterpillar.") {
    /* 由于 Map 和 Set 在内部按排序顺序存储条目，因此该顺序
     * 做决策时遍历人员的顺序会影响结果
     * 结果会受这些人员姓名顺序影响。此测试使用类似如下的分组：
     * 此测试尝试人员姓名的所有可能排列：
     *
     *         *---*---*
     *         |   |   |
     *         *   *   *
     *
     * 这六个项目共有 6! = 720 种可能的排列
     * 人员。如果代码能够针对所有这些情况正确解决问题，
     * 若这些排列都能通过，很可能说明你正确跟踪了
     * 每一步谁与谁配对。另一方面，如果代码出现
     * 若这里出现问题，可能表示标记配对状态的方式存在错误：
     * 谁已配对、谁未配对。
     */
    Vector<string> people = { "A", "B", "C", "D", "E", "F" };
    do {
        Map<string, Set<string>> links = fromLinks({
            { people[0], people[1] },
            { people[1], people[2] },
            { people[0], people[3] },
            { people[1], people[4] },
            { people[2], people[5] },
        });

        Set<Pair> matching;
        EXPECT(hasPerfectMatching(links, matching));
        EXPECT(isPerfectMatching(links, matching));
    } while (next_permutation(people.begin(), people.end()));
}

PROVIDED_TEST("hasPerfectMatching stress test: negative example (should take under a second).") {
    /* 这里，我们给出一个像这样的人员“毛毛虫”结构：
     *
     *    *   *   *   *     *   *
     *    |   |   |   |     |   |
     *    *---*---*---* ... *---*
     *    |   |   |   |     |   |
     *    *   *   *   *     *   *
     *
     * 这里不存在完美匹配。不过，可能需要进行一些搜索
     * 确认确实如此。不过，在此规模下，它应当
     * 几乎可以瞬间找到解，因为搜索空间相当
     * 规模较小，并且大多数“错误”决策都能被快速检测出来。
     *
     * 另一方面，若实现反复构造相同的
     * 反复进行匹配，或者即使某个已经
     * 若找到无法与当前配置配对的对象，则其数量
     * 需要考虑的选项数量将大到计算机无法处理
     * 在合理时间内无法完成。
     *
     * 若其他测试均通过但此测试卡住，请再次检查
     * 检查代码，确保没有反复构造相同的配对
     * 多次。
     */

    /* “身体节段”的数量。 */
    const int kRowSize = 10;

    Vector<Pair> links;
    for (int i = 0; i < kRowSize - 1; i++) {
        links.add({ to_string(i), to_string(i + 1) });
    }
    for (int i = 0; i < kRowSize; i++) {
        links.add({ to_string(i), to_string(i + kRowSize) });
    }
    for (int i = 0; i < kRowSize; i++) {
        links.add({ to_string(i), to_string(i + 2 * kRowSize) });
    }

    Set<Pair> matching;
    EXPECT(!hasPerfectMatching(fromLinks(links), matching));
}

PROVIDED_TEST("hasPerfectMatching stress test: positive example (should take under a second).") {
    /* 这里，我们给出一个像这样的人员“千足虫”结构：
     *
     *    *---*---*---* ... *---*
     *    |   |   |   |     |   |
     *    *   *   *   *     *   *
     *
     * 这里始终存在完美匹配，可通过将每个人
     * 与其正下方的人配对。不过，可能需要进行一些搜索
     * 找到这一特定配置。不过，在此规模下，它应当
     * 几乎可以瞬间找到解，因为搜索空间相当
     * 规模较小，并且大多数“错误”决策都能被快速检测出来。
     *
     * 另一方面，若实现反复构造相同的
     * 反复进行匹配，或者即使某个已经
     * 若找到无法与当前配置配对的对象，则其数量
     * 需要考虑的选项数量将大到计算机无法处理
     * 在合理时间内无法完成。
     *
     * 若其他测试均通过但此测试卡住，请再次检查
     * 检查代码，确保没有反复构造相同的配对
     * 多次。
     */

    /* “身体节段”的数量。 */
    const int kRowSize = 10;

    Vector<Pair> links;
    for (int i = 0; i < kRowSize - 1; i++) {
        links.add({ to_string(i), to_string(i + 1) });
    }
    for (int i = 0; i < kRowSize; i++) {
        links.add({ to_string(i), to_string(i + kRowSize) });
    }

    Set<Pair> matching;
    EXPECT(hasPerfectMatching(fromLinks(links), matching));
    EXPECT(isPerfectMatching(fromLinks(links), matching));
}

PROVIDED_TEST("maximumWeightMatching: Works for empty group.") {
    EXPECT_EQUAL(maximumWeightMatching({}), {});
}

PROVIDED_TEST("maximumWeightMatching: Works for group of one person.") {
    Map<string, Map<string, int>> links = {
        { "A", {} }
    };

    EXPECT_EQUAL(maximumWeightMatching(links), {});
}

PROVIDED_TEST("maximumWeightMatching: Works for a single pair of people.") {
    /* 当前世界：
     *
     *  A --- B
     *     1
     *
     * 最佳选择是 A -- B。
     */
    auto links = fromWeightedLinks({
        { "A", "B", 1 }
    });

    /* 应选择 A--B。 */
    EXPECT_EQUAL(maximumWeightMatching(links), {{"A", "B"}});
}

PROVIDED_TEST("maximumWeightMatching: Won't pick a negative edge.") {
    /* 当前世界：
     *
     *  A --- B
     *     -1
     *
     * 最佳选择是不匹配任何人！
     */
    auto links = fromWeightedLinks({
        { "A", "B", -1 }
    });

    /* 应选择 A--B。 */
    EXPECT_EQUAL(maximumWeightMatching(links), {});
}

PROVIDED_TEST("maximumWeightMatching: Works on a line of three people.") {
    /* 当前世界：
     *
     *  A --- B --- C
     *     1     2
     *
     * 最佳选项是选择 B -- C。
     */
    auto links = fromWeightedLinks({
        { "A", "B", 1 },
        { "B", "C", 2 },
    });

    /* 应当选择 B--C。 */
    EXPECT_EQUAL(maximumWeightMatching(links), { {"B", "C"} });
}

PROVIDED_TEST("maximumWeightMatching: Works on a triangle.") {
    /* 当前世界：
     *
     *         A
     *      1 / \ 2
     *       B---C
     *         3
     *
     * 最佳选项是选择 B -- C。
     */
    auto links = fromWeightedLinks({
        { "A", "B", 1 },
        { "B", "C", 3 },
        { "A", "C", 2 }
    });

    /* 应当选择 B--C。 */
    EXPECT_EQUAL(maximumWeightMatching(links), { {"B", "C"} });
}

PROVIDED_TEST("maximumWeightMatching: Works on a square.") {
    /* 当前世界：
     *
     *         1
     *      A --- B
     *      |     |
     *    8 |     | 2
     *      |     |
     *      D --- C
     *         4
     *
     * 最佳选择是 BC/AD。
     */
    auto links = fromWeightedLinks({
        { "A", "B", 1 },
        { "B", "C", 2 },
        { "C", "D", 4 },
        { "D", "A", 8 },
    });

    EXPECT_EQUAL(maximumWeightMatching(links), { {"A", "D"}, {"B", "C"} });
}

PROVIDED_TEST("maximumWeightMatching: Works on a line of four people.") {
    /* 当前世界：
     *
     *  A --- B --- C --- D
     *     1     3     1
     *
     * 最佳选择是 B -- C，尽管这不是完美
     * 匹配。
     */
    auto links = fromWeightedLinks({
        { "A", "B", 1 },
        { "B", "C", 3 },
        { "C", "D", 1 },
    });

    /* 应当选择 B--C。 */
    EXPECT_EQUAL(maximumWeightMatching(links), { {"B", "C"} });
}

PROVIDED_TEST("maximumWeightMatching: Small stress test (should take at most a second or two).") {
    /* 由于 Map 和 Set 在内部按排序顺序存储条目，因此该顺序
     * 做决策时遍历人员的顺序会影响结果
     * 结果会受这些人员姓名顺序影响。此测试使用类似如下的分组：
     * 此测试尝试人员姓名的所有可能排列：
     *
     *               *
     *               | 1
     *               *
     *            1 / \ 5
     *             *---*
     *          1 /  1  \ 1
     *           *       *
     *
     * （最佳选择是选取成本为 5 的边和另一侧成本为 1 的边
     * 边。）
     *
     * 这些项的排列顺序共有 6! = 720 种可能
     * 人员。如果代码能够针对所有这些情况正确解决问题，
     * 若这些排列都能通过，很可能说明你正确跟踪了
     * 每一步谁与谁配对。另一方面，如果代码出现
     * 若这里出现问题，可能表示标记配对状态的方式存在错误：
     * 谁已配对、谁未配对。
     */
    Vector<string> people = { "A", "B", "C", "D", "E", "F" };
    do {
        auto links = fromWeightedLinks({
            { people[0], people[1], 5 },
            { people[1], people[2], 1 },
            { people[2], people[0], 1 },
            { people[3], people[0], 1 },
            { people[4], people[1], 1 },
            { people[5], people[2], 1 },
        });

        Set<Pair> expected = {
            { people[0], people[1] },
            { people[2], people[5] }
        };

        EXPECT_EQUAL(maximumWeightMatching(links), expected);
    } while (next_permutation(people.begin(), people.end()));
}

PROVIDED_TEST("maximumWeightMatching: Large stress test (should take at most a second or two).") {
    /* 这里，我们给出一条像这样的人员链：
     *
     *    *---*---*---*---*---*---*---* ... *---*
     *      1   1   1   1   1   1   1         1
     *
     * n 个人排成一列时，不同配对方式的数量由
     * 第 n 个 Fibonacci 数。（很好的练习——你能解释原因吗？）这意味着
     * 如果有一条包含 21 人的链，则有 F(21) = 10,946 种可能的
     * 要检查的匹配。如果程序恰好逐一测试所有匹配
     * 一次，那么确定最佳匹配应当很快
     * 这里是。（它是任何恰好使用 floor(21 / 2) = 10 条边的匹配。
     *
     * 另一方面，若实现反复构造相同的
     * 反复枚举匹配时，需要考虑的选项数量
     * 在任何合理时间内都大到计算机无法处理。
     *
     * 若其他测试均通过但此测试卡住，请再次检查
     * 检查代码，确保没有反复构造相同的配对
     * 多次。
     */
    const int kNumPeople = 21;
    Vector<WeightedLink> links;
    for (int i = 0; i < kNumPeople - 1; i++) {
        links.add({ to_string(i), to_string(i + 1), 1 });
    }

    auto matching = maximumWeightMatching(fromWeightedLinks(links));
    EXPECT_EQUAL(matching.size(), kNumPeople / 2);

    /* 确认它是一个匹配。 */
    Set<string> used;
    for (Pair p: matching) {
        /* 没有任何人被配对超过一次。 */
        EXPECT(!used.contains(p.first()));
        EXPECT(!used.contains(p.second()));
        used += p.first();
        used += p.second();

        /* 必须是可能的链接。 */
        EXPECT_EQUAL(abs(stringToInteger(p.first()) - stringToInteger(p.second())), 1);
    }
}
