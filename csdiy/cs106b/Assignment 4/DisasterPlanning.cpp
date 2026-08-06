#include "DisasterPlanning.h"
using namespace std;

/* TODO：有关此函数的更多信息，请参阅 DisasterPlanning.h。
 * 然后删除此注释。
 */
bool canBeMadeDisasterReady(const Map<string, Set<string>>& roadNetwork,
                            int numCities,
                            Set<string>& supplyLocations) {
    /* TODO：删除接下来的几行并实现此函数。 */
    (void) roadNetwork;
    (void) numCities;
    (void) supplyLocations;
    return false;
}


/* * * * * * * 此处以下为测试辅助函数 * * * * * */
#include "GUI/SimpleTest.h"

/* 这是一个有助于设计测试用例的辅助函数。你向它提供一个 Map
 * 城市及其相邻城市，然后生成一个新的 Map，其中如果城市
 * A 连接到城市 B，则城市 B 也连接回城市 A。我们建议使用此辅助函数
 * 编写测试时使用的函数，不过在主实现中不需要
 * canBeMadeDisasterReady 函数。
 */
Map<string, Set<string>> makeSymmetric(const Map<string, Set<string>>& source) {
    Map<string, Set<string>> result = source;

    for (const string& from: source) {
        for (const string& to: source[from]) {
            result[from] += to;
            result[to] += from;
        }
    }

    return result;
}

/* 此辅助函数测试某个城市是否已被一组补给地点覆盖
 * 并由我们的测试代码使用。也欢迎在你自己的测试中使用它！
 */
bool isCovered(const string& city,
               const Map<string, Set<string>>& roadNetwork,
               const Set<string>& supplyLocations) {
    if (supplyLocations.contains(city)) return true;

    for (string neighbor: roadNetwork[city]) {
        if (supplyLocations.contains(neighbor)) return true;
    }

    return false;
}

/* * * * * * 此处以下为测试用例 * * * * * */

/* TODO：在此添加你自己的自定义测试！ */














/* * * * * 此处以下为提供的测试 * * * * */

PROVIDED_TEST("Reports an error if numCities < 0") {
    Set<string> supply;
    EXPECT_ERROR(canBeMadeDisasterReady({}, -137, supply));
}

PROVIDED_TEST("Works for map with no cities.") {
    Set<string> locations;

    /* 这里使用多少个城市其实并不重要。 */
    EXPECT(canBeMadeDisasterReady({}, 0, locations));
    EXPECT_EQUAL(locations.size(), 0);

    EXPECT(canBeMadeDisasterReady({}, 137, locations));
    EXPECT_EQUAL(locations.size(), 0);
}

PROVIDED_TEST("Works for map with one city.") {
    Map<string, Set<string>> map = makeSymmetric({
         { "Solipsist", {} }
    });

    /* 使用多少城市都不重要，只要不为零！ */
    Set<string> locations0, locations1, locations2;
    EXPECT(!canBeMadeDisasterReady(map, 0, locations0));
    EXPECT( canBeMadeDisasterReady(map, 1, locations1));
    EXPECT( canBeMadeDisasterReady(map, 2, locations2));
}

PROVIDED_TEST("Works for map with one city, and produces output.") {
    Map<string, Set<string>> map = makeSymmetric({
         { "Solipsist", {} }
    });

    Set<string> locations0, locations1, locations2;
    EXPECT(!canBeMadeDisasterReady(map, 0, locations0));
    EXPECT(canBeMadeDisasterReady(map, 1, locations1));
    EXPECT(canBeMadeDisasterReady(map, 2, locations2));

    /* 不要检查 locations0；由于函数返回 false，其中的值
     * 可以是任何内容。
     */
    Set<string> expected = { "Solipsist" };
    EXPECT_EQUAL(locations1, expected);
    EXPECT_EQUAL(locations2, expected);
}

PROVIDED_TEST("Works for map with two linked cities.") {
    Map<string, Set<string>> map = makeSymmetric({
         { "A", { "B" } },
         { "B", {     } }
    });

    Set<string> locations0, locations1, locations2;
    EXPECT(!canBeMadeDisasterReady(map, 0, locations0));
    EXPECT(canBeMadeDisasterReady(map, 1, locations1));
    EXPECT(canBeMadeDisasterReady(map, 2, locations2));
}

PROVIDED_TEST("Works for map with two linked cities, and produces output.") {
    Map<string, Set<string>> map = makeSymmetric({
         { "A", { "B" } },
    });

    Set<string> locations0, locations1, locations2;
    EXPECT(!canBeMadeDisasterReady(map, 0, locations0));
    EXPECT(canBeMadeDisasterReady(map, 1, locations1));
    EXPECT(canBeMadeDisasterReady(map, 2, locations2));

    EXPECT_EQUAL(locations1.size(), 1);
    EXPECT(locations1.isSubsetOf({"A", "B"}));

    EXPECT(locations2.size() <= 2);
    EXPECT(locations2.isSubsetOf({"A", "B"}));
}

PROVIDED_TEST("Works for four disconnected cities.") {
    Map<string, Set<string>> map = makeSymmetric({
        { "A", { } },
        { "B", { } },
        { "C", { } },
        { "D", { } }
    });

    Set<string> locations0, locations1, locations2, locations3, locations4;
    EXPECT(!canBeMadeDisasterReady(map, 0, locations0));
    EXPECT(!canBeMadeDisasterReady(map, 1, locations1));
    EXPECT(!canBeMadeDisasterReady(map, 2, locations2));
    EXPECT(!canBeMadeDisasterReady(map, 3, locations3));
    EXPECT(canBeMadeDisasterReady(map, 4, locations4));
}

PROVIDED_TEST("Works for four disconnected cities, and produces output.") {
    Map<string, Set<string>> map = makeSymmetric({
        { "A", { } },
        { "B", { } },
        { "C", { } },
        { "D", { } }
    });

    Set<string> locations0, locations1, locations2, locations3, locations4;
    EXPECT(!canBeMadeDisasterReady(map, 0, locations0));
    EXPECT(!canBeMadeDisasterReady(map, 1, locations1));
    EXPECT(!canBeMadeDisasterReady(map, 2, locations2));
    EXPECT(!canBeMadeDisasterReady(map, 3, locations3));
    EXPECT(canBeMadeDisasterReady(map, 4, locations4));

    Set<string> expected = { "A", "B", "C", "D" };
    EXPECT_EQUAL(locations4, expected);
}

PROVIDED_TEST("Can solve ethene example, regardless of ordering.") {
    /* 由于 Map 和 Set 在内部按排序顺序存储条目，因此该顺序
     * 做决策时遍历城市的顺序会影响结果
     * 结果会受这些城市名称顺序影响。此测试使用类似如下的地图：
     * 此测试尝试城市名称的所有可能排列：
     *
     *             *
     *             |
     *        * -- * -- * -- *
     *                  |
     *                  *
     *
     * 这六个项目共有 6! = 720 种可能的排列
     * 城市。如果代码能针对所有这些情况正确解决问题，
     * 若这些排列均能通过，很可能说明你正确地
     * 在每一步覆盖或取消覆盖城市。另一方面，如果
     * 若代码在这里出现问题，可能表示以下操作方式存在错误：
     * 覆盖和取消覆盖城市时，意外取消了一个城市的覆盖，而该城市
     * 之前已经覆盖的内容。
     */
    Vector<string> cities = { "A", "B", "C", "D", "E", "F" };
    do {
        /* 乙烯排列：
         *
         *        0
         *       1234
         *         5
         */
        Map<string, Set<string>> map = makeSymmetric({
            { cities[2], { cities[0], cities[1], cities[3] } },
            { cities[3], { cities[4], cities[5] } }
        });

        /* 我们应当能用两个城市覆盖所有地点：
         * 城市 2 和城市 3。
         */
        Set<string> chosen;
        EXPECT(canBeMadeDisasterReady(map, 2, chosen));

        /* 不应能只用一个城市覆盖所有位置。 */
        chosen.clear();
        EXPECT(!canBeMadeDisasterReady(map, 1, chosen));
    } while (next_permutation(cities.begin(), cities.end()));
}

PROVIDED_TEST("Can solve ethene example, regardless of ordering, and produces output.") {
    /* 由于 Map 和 Set 在内部按排序顺序存储条目，因此该顺序
     * 做决策时遍历城市的顺序会影响结果
     * 结果会受这些城市名称顺序影响。此测试使用类似如下的地图：
     * 此测试尝试城市名称的所有可能排列：
     *
     *             *
     *             |
     *        * -- * -- * -- *
     *                  |
     *                  *
     *
     * 这六个项目共有 6! = 720 种可能的排列
     * 城市。如果代码能针对所有这些情况正确解决问题，
     * 若这些排列均能通过，很可能说明你正确地
     * 在每一步覆盖或取消覆盖城市。另一方面，如果
     * 若代码在这里出现问题，可能表示以下操作方式存在错误：
     * 覆盖和取消覆盖城市时，意外取消了一个城市的覆盖，而该城市
     * 之前已经覆盖的内容。
     */
    Vector<string> cities = { "A", "B", "C", "D", "E", "F" };
    do {
        /* 乙烯排列：
         *
         *        0
         *       1234
         *         5
         */
        Map<string, Set<string>> map = makeSymmetric({
            { cities[2], { cities[0], cities[1], cities[3] } },
            { cities[3], { cities[4], cities[5] } }
        });

        /* 我们应当能用两个城市覆盖所有地点：
         * 城市 2 和城市 3。
         */
        Set<string> chosen;
        EXPECT(canBeMadeDisasterReady(map, 2, chosen));

        EXPECT_EQUAL(chosen.size(), 2);
        EXPECT(chosen.contains(cities[2]));
        EXPECT(chosen.contains(cities[3]));

        /* 不应能只用一个城市覆盖所有位置。 */
        chosen.clear();
        EXPECT(!canBeMadeDisasterReady(map, 1, chosen));
    } while (next_permutation(cities.begin(), cities.end()));
}

PROVIDED_TEST("Works for six cities in a line, regardless of order.") {
    /* 由于 Map 和 Set 在内部按排序顺序存储条目，因此该顺序
     * 做决策时遍历城市的顺序会影响结果
     * 结果会受这些城市名称顺序影响。此测试使用类似如下的地图：
     * 此测试尝试城市名称的所有可能排列：
     *
     *        * -- * -- * -- * -- * -- *
     *
     * 这六个项目共有 6! = 720 种可能的排列
     * 排成一行的城市。如果代码能够正确解决问题
     * 若所有这些排列都能通过，很可能说明你正确地
     * 在每一步覆盖或取消覆盖城市。另一方面，如果
     * 若代码在这里出现问题，可能表示以下操作方式存在错误：
     * 覆盖和取消覆盖城市时，意外取消了一个城市的覆盖，而该城市
     * 之前已经覆盖的内容。
     */
    Vector<string> cities = { "A", "B", "C", "D", "E", "F" };
    do {
        /* 线性排列。 */
        Map<string, Set<string>> map;
        for (int i = 1; i + 1 < cities.size(); i++) {
            map[cities[i]] = { cities[i - 1], cities[i + 1] };
        }

        map = makeSymmetric(map);

        /* 我们应当能用两个城市覆盖所有地点，具体是
         * 距离两侧各向内一个位置的城市。
         */
        Set<string> chosen;
        EXPECT(canBeMadeDisasterReady(map, 2, chosen));

        /* 不应能只用一个城市覆盖所有位置。 */
        chosen.clear();
        EXPECT(!canBeMadeDisasterReady(map, 1, chosen));
    } while (next_permutation(cities.begin(), cities.end()));
}

PROVIDED_TEST("Works for six cities in a line, regardless of order, and produces output.") {
    /* 由于 Map 和 Set 在内部按排序顺序存储条目，因此该顺序
     * 做决策时遍历城市的顺序会影响结果
     * 结果会受这些城市名称顺序影响。此测试使用类似如下的地图：
     * 此测试尝试城市名称的所有可能排列：
     *
     *        * -- * -- * -- * -- * -- *
     *
     * 这六个项目共有 6! = 720 种可能的排列
     * 排成一行的城市。如果代码能够正确解决问题
     * 若所有这些排列都能通过，很可能说明你正确地
     * 在每一步覆盖或取消覆盖城市。另一方面，如果
     * 若代码在这里出现问题，可能表示以下操作方式存在错误：
     * 覆盖和取消覆盖城市时，意外取消了一个城市的覆盖，而该城市
     * 之前已经覆盖的内容。
     */
    Vector<string> cities = { "A", "B", "C", "D", "E", "F" };
    do {
        /* 线性排列。 */
        Map<string, Set<string>> map;
        for (int i = 1; i + 1 < cities.size(); i++) {
            map[cities[i]] = { cities[i - 1], cities[i + 1] };
        }

        map = makeSymmetric(map);

        /* 我们应当能用两个城市覆盖所有地点，具体是
         * 距离两侧各向内一个位置的城市。
         */
        Set<string> chosen;
        EXPECT(canBeMadeDisasterReady(map, 2, chosen));

        EXPECT_EQUAL(chosen.size(), 2);
        EXPECT(chosen.contains(cities[1]));
        EXPECT(chosen.contains(cities[4]));

        /* 不应能只用一个城市覆盖所有位置。 */
        chosen.clear();
        EXPECT(!canBeMadeDisasterReady(map, 1, chosen));
    } while (next_permutation(cities.begin(), cities.end()));
}

/* “Don't Be Greedy”示例世界。 */
const Map<string, Set<string>> kDontBeGreedy = makeSymmetric({
    { "A", { "B" } },
    { "B", { "C", "D" } },
    { "C", { "D" } },
    { "D", { "F", "G" } },
    { "E", { "F" } },
    { "F", { "G" } },
});

PROVIDED_TEST("Solves \"Don't be Greedy\" from the handout.") {
    Set<string> locations0, locations1, locations2;
    EXPECT(!canBeMadeDisasterReady(kDontBeGreedy, 0, locations0));
    EXPECT(!canBeMadeDisasterReady(kDontBeGreedy, 1, locations1));
    EXPECT( canBeMadeDisasterReady(kDontBeGreedy, 2, locations2));
}

PROVIDED_TEST("Solves \"Don't be Greedy\" from the handout, and produces output.") {
    Set<string> locations0, locations1, locations2;
    EXPECT(!canBeMadeDisasterReady(kDontBeGreedy, 0, locations0));
    EXPECT(!canBeMadeDisasterReady(kDontBeGreedy, 1, locations1));
    EXPECT( canBeMadeDisasterReady(kDontBeGreedy, 2, locations2));

    Set<string> expected = {"B", "F"};
    EXPECT_EQUAL(locations2, expected);
}

PROVIDED_TEST("Solves \"Don't be Greedy,\" regardless of ordering, and produces output.") {
    /* 由于 Map 和 Set 在内部按排序顺序存储条目，因此该顺序
     * 做决策时遍历城市的顺序会影响结果
     * 结果会受这些城市名称顺序影响。此测试使用类似如下的地图：
     * 此测试尝试城市名称的所有可能排列：
     *
     *     0       4
     *     |       |
     *     1 - 2 - 3
     *      \ / \ /
     *       5   6
     *
     * 这七个元素的排列顺序共有 7! = 5,040 种可能
     * 城市。如果代码能针对所有这些情况正确解决问题，
     * 若这些排列均能通过，很可能说明你正确地
     * 在每一步覆盖或取消覆盖城市。另一方面，如果
     * 若代码在这里出现问题，可能表示以下操作方式存在错误：
     * 覆盖和取消覆盖城市时，意外取消了一个城市的覆盖，而该城市
     * 之前已经覆盖的内容。
     */
    Vector<string> cities = { "A", "B", "C", "D", "E", "F", "G" };
    do {
        Map<string, Set<string>> map = makeSymmetric({
            { cities[1], { cities[0], cities[2], cities[5] } },
            { cities[2], { cities[3], cities[5], cities[6] } },
            { cities[3], { cities[4], cities[6] } },
        });

        /* 我们应能用两个城市覆盖全部区域。 */
        Set<string> chosen;
        EXPECT(canBeMadeDisasterReady(map, 2, chosen));

        /* 这些城市应为 1 和 3。 */
        EXPECT_EQUAL(chosen, { cities[1], cities[3] });

        /* 不应能只用一个城市覆盖所有位置。 */
        chosen.clear();
        EXPECT(!canBeMadeDisasterReady(map, 1, chosen));
    } while (next_permutation(cities.begin(), cities.end()));
}

PROVIDED_TEST("Stress test: 6 x 6 grid. (This should take at most a few seconds.)") {
    Map<string, Set<string>> grid;

    /* 构建网格。 */
    char maxRow = 'F';
    int  maxCol = 6;
    for (char row = 'A'; row <= maxRow; row++) {
        for (int col = 1; col <= maxCol; col++) {
            if (row != maxRow) {
                grid[row + to_string(col)] += (char(row + 1) + to_string(col));
            }
            if (col != maxCol) {
                grid[row + to_string(col)] += (char(row) + to_string(col + 1));
            }
        }
    }
    grid = makeSymmetric(grid);

    Set<string> locations;
    EXPECT(canBeMadeDisasterReady(grid, 10, locations));
}

PROVIDED_TEST("Stress test: 6 x 6 grid, with output. (This should take at most a few seconds.)") {
    Map<string, Set<string>> grid;

    /* 构建网格。 */
    char maxRow = 'F';
    int  maxCol = 6;
    for (char row = 'A'; row <= maxRow; row++) {
        for (int col = 1; col <= maxCol; col++) {
            if (row != maxRow) {
                grid[row + to_string(col)] += (char(row + 1) + to_string(col));
            }
            if (col != maxCol) {
                grid[row + to_string(col)] += (char(row) + to_string(col + 1));
            }
        }
    }
    grid = makeSymmetric(grid);

    Set<string> locations;
    EXPECT(canBeMadeDisasterReady(grid, 10, locations));

    for (char row = 'A'; row <= maxRow; row++) {
        for (int col = 1; col <= maxCol; col++) {
            EXPECT(isCovered(row + to_string(col), grid, locations));
        }
    }
}

