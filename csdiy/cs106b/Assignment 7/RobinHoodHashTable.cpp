#include "RobinHoodHashTable.h"
using namespace std;

RobinHoodHashTable::RobinHoodHashTable(HashFunction<string> hashFn) {
    /* TODO：删除此注释，然后实现此函数。 */
    (void) hashFn;
}

RobinHoodHashTable::~RobinHoodHashTable() {
    /* TODO：删除此注释，然后实现此函数。 */
}

int RobinHoodHashTable::size() const {
    /* TODO：删除此注释及下一行，然后实现此函数。 */
    return -1;
}

bool RobinHoodHashTable::isEmpty() const {
    /* TODO：删除此注释及下一行，然后实现此函数。 */
    return false;
}

bool RobinHoodHashTable::insert(const string& elem) {
    /* TODO：删除此注释及接下来的几行，然后实现此函数。 */
    (void) elem;
    return false;
}

bool RobinHoodHashTable::contains(const string& elem) const {
    /* TODO：删除此注释及接下来的几行，然后实现此函数。 */
    (void) elem;
    return false;
}

bool RobinHoodHashTable::remove(const string& elem) {
    /* TODO：删除此注释及接下来的几行，然后实现此函数。 */
    (void) elem;
    return false;
}

void RobinHoodHashTable::printDebugInfo() const {
    /* TODO：删除此注释并实现此函数。 */
}


/* * * * * * 此处以下为测试用例 * * * * * */
#include "GUI/SimpleTest.h"

/* 可选：在此添加你自己的自定义测试！ */














/* * * * * 此处以下为提供的测试 * * * * */
#include "Demos/Utility.h"
#include "vector.h"

PROVIDED_TEST("Table is initially empty.") {
    RobinHoodHashTable table(Hash::random(10));

    EXPECT_EQUAL(table.size(), 0);
    EXPECT(table.isEmpty());

    /* 检查表的内部状态。 */
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].distance, RobinHoodHashTable::EMPTY_SLOT);
    }
}

PROVIDED_TEST("Can insert and look up a single value.") {
    RobinHoodHashTable table(Hash::identity(10));

    EXPECT(!table.contains("0"));
    EXPECT(table.insert("0"));
    EXPECT(table.contains("0"));

    /* 检查表的内部状态。 */
    EXPECT_EQUAL(table.elems[0], { "0", 0 });
    for (int i = 1; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].distance, RobinHoodHashTable::EMPTY_SLOT);
    }
}

PROVIDED_TEST("Is case-sensitive.") {
    RobinHoodHashTable table(Hash::zero(10));

    EXPECT(!table.contains("a"));
    EXPECT(!table.contains("A"));
    EXPECT(table.insert("a"));

    /* 检查表的内部状态。 */
    EXPECT_EQUAL(table.elems[0], { "a", 0 });
    for (int i = 1; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].distance, RobinHoodHashTable::EMPTY_SLOT);
    }

    EXPECT(table.contains("a"));
    EXPECT(!table.contains("A"));
}

PROVIDED_TEST("Insertions work with hash collisions.") {
    /* 使用一个非常、非常糟糕的哈希函数，将所有内容都映射到槽位零。 */
    RobinHoodHashTable table(Hash::zero(10));

    Vector<string> toAdd = {
        "Quokka", "Pudu", "Gerenuk", "Dikdik"
    };
    Vector<string> toNotAdd = {
        "Springbok", "Kudu"
    };

    for (string animal: toAdd) {
        EXPECT(table.insert(animal));
    }
    EXPECT_EQUAL(table.size(), toAdd.size());

    /* 验证内部状态。第一个表格应如下所示：
     *
     * Quokka Pudu Gerenuk Dikdik（空）（空）（空）（空）（空）（空）
     *   0      1     2      3
     */
    for (int i = 0; i < 10; i++) {
        if (i < toAdd.size()) {
            EXPECT_EQUAL(table.elems[i], { toAdd[i], i });
        } else {
            EXPECT_EQUAL(table.elems[i].distance, RobinHoodHashTable::EMPTY_SLOT);
        }
    }

    for (string animal: toAdd) {
        EXPECT(table.contains(animal));
    }
    for (string animal: toNotAdd) {
        EXPECT(!table.contains(animal));
    }
}

PROVIDED_TEST("Insertions don't displace items at same distance from home.") {
    /* 所用哈希函数将字符串映射到其数值。这使我们能够
     * 使我们能够控制哈希表内容。
     */
    RobinHoodHashTable table(Hash::identity(10));

    /* 放入 0 和 10。此时该表应如下所示：
     *
     *            0 10 . . . . . . . .
     *            0  1
     *
     */
    EXPECT(table.insert("0"));
    EXPECT(table.insert("10"));

    EXPECT_EQUAL(table.elems[0], {  "0", 0 });
    EXPECT_EQUAL(table.elems[1], { "10", 1 });

    for (int i = 2; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].distance, RobinHoodHashTable::EMPTY_SLOT);
    }

    EXPECT(table.contains("0"));
    EXPECT(table.contains("10"));

    /* 现在插入值 1、2、3、4 和 5。该表应如下所示：
     * 如下所示：
     *
     *           0 10  1  2  3  4  5  .  .  .
     *           0  1  1  1  1  1  1
     */
    EXPECT(table.insert("1"));
    EXPECT(table.insert("2"));
    EXPECT(table.insert("3"));
    EXPECT(table.insert("4"));
    EXPECT(table.insert("5"));

    EXPECT_EQUAL(table.elems[0], {  "0", 0 });
    EXPECT_EQUAL(table.elems[1], { "10", 1 });
    EXPECT_EQUAL(table.elems[2], {  "1", 1 });
    EXPECT_EQUAL(table.elems[3], {  "2", 1 });
    EXPECT_EQUAL(table.elems[4], {  "3", 1 });
    EXPECT_EQUAL(table.elems[5], {  "4", 1 });
    EXPECT_EQUAL(table.elems[6], {  "5", 1 });
    EXPECT_EQUAL(table.elems[7].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[8].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[9].distance, RobinHoodHashTable::EMPTY_SLOT);

    /* 确保我们能找到所有内容。 */
    EXPECT(table.contains("0"));
    EXPECT(table.contains("1"));
    EXPECT(table.contains("2"));
    EXPECT(table.contains("3"));
    EXPECT(table.contains("4"));
    EXPECT(table.contains("5"));
    EXPECT(!table.contains("6"));
    EXPECT(!table.contains("7"));
    EXPECT(!table.contains("8"));
    EXPECT(!table.contains("9"));
    EXPECT(table.contains("10"));

    EXPECT_EQUAL(table.size(), 7);
}

PROVIDED_TEST("Insertions displace elements that are closer to home.") {
    /* 所用哈希函数将字符串映射到其数值。这使我们能够
     * 使我们能够控制哈希表内容。
     */
    RobinHoodHashTable table(Hash::identity(10));

    /* 插入一系列元素，恢复为此表：
     *
     *   .  1  .  3  .  .  6  .  .  .
     *      0     0        0
     */
    EXPECT(table.insert("1"));
    EXPECT(table.insert("3"));
    EXPECT(table.insert("6"));

    EXPECT_EQUAL(table.elems[0].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[1], {  "1", 0 });
    EXPECT_EQUAL(table.elems[2].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[3], {  "3", 0 });
    EXPECT_EQUAL(table.elems[4].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[5].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[6], {  "6", 0 });
    EXPECT_EQUAL(table.elems[7].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[8].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[9].distance, RobinHoodHashTable::EMPTY_SLOT);

    EXPECT_EQUAL(table.size(), 3);

    /* 插入 13 和 23，得到此表：
     *
     *   .  1  .  3 13 23  6  .  .  .
     *      0     0  1  2  0
     */
    EXPECT(table.insert("13"));
    EXPECT(table.insert("23"));

    EXPECT_EQUAL(table.elems[0].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[1], {  "1", 0 });
    EXPECT_EQUAL(table.elems[2].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[3], {  "3", 0 });
    EXPECT_EQUAL(table.elems[4], { "13", 1 });
    EXPECT_EQUAL(table.elems[5], { "23", 2 });
    EXPECT_EQUAL(table.elems[6], {  "6", 0 });
    EXPECT_EQUAL(table.elems[7].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[8].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[9].distance, RobinHoodHashTable::EMPTY_SLOT);

    EXPECT_EQUAL(table.size(), 5);

    /* 插入 5，得到此表：
     *
     *   .  1  .  3 13 23  5  6  .  .
     *      0     0  1  2  1  1
     */
    EXPECT(table.insert("5"));

    EXPECT_EQUAL(table.elems[0].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[1], {  "1", 0 });
    EXPECT_EQUAL(table.elems[2].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[3], {  "3", 0 });
    EXPECT_EQUAL(table.elems[4], { "13", 1 });
    EXPECT_EQUAL(table.elems[5], { "23", 2 });
    EXPECT_EQUAL(table.elems[6], {  "5", 1 });
    EXPECT_EQUAL(table.elems[7], {  "6", 1 });
    EXPECT_EQUAL(table.elems[8].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[9].distance, RobinHoodHashTable::EMPTY_SLOT);

    EXPECT_EQUAL(table.size(), 6);

    /* 插入 11，得到此表：
     *
     *   .  1 11  3 13 23  5  6  .  .
     *      0  1  0  1  2  1  1
     */
    EXPECT(table.insert("11"));

    EXPECT_EQUAL(table.elems[0].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[1], {  "1", 0 });
    EXPECT_EQUAL(table.elems[2], { "11", 1 });
    EXPECT_EQUAL(table.elems[3], {  "3", 0 });
    EXPECT_EQUAL(table.elems[4], { "13", 1 });
    EXPECT_EQUAL(table.elems[5], { "23", 2 });
    EXPECT_EQUAL(table.elems[6], {  "5", 1 });
    EXPECT_EQUAL(table.elems[7], {  "6", 1 });
    EXPECT_EQUAL(table.elems[8].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[9].distance, RobinHoodHashTable::EMPTY_SLOT);

    EXPECT_EQUAL(table.size(), 7);

    /* 插入 21。这会触发一连串位移，最终如下：
     *
     *   .  1 11  21 13 23  3  5  6  .
     *      0  1  2   1  2  3  2  2
     *
     *  为什么 3 最终位于 13 和 23 之后？因为当 3 被移位时
     *  最初，它距初始位置一个槽位，而下一个槽位（13）是
     *  也距离原位一个槽位。我们的规则是绝不移动某个元素
     *  除非某元素严格比我们更接近其初始位置，否则它不会位于表中；在这种
     *  情况下出现平局。然后，将 3 与下一个槽位（23）比较时，我们
     *  同样出现并列（两者距离均为 2），因此不将其交换进来。
     *  不过，3 确实能放入下一个槽位。
     */
    EXPECT(table.insert("21"));

    EXPECT_EQUAL(table.elems[0].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[1], {  "1", 0 });
    EXPECT_EQUAL(table.elems[2], { "11", 1 });
    EXPECT_EQUAL(table.elems[3], { "21", 2 });
    EXPECT_EQUAL(table.elems[4], { "13", 1 });
    EXPECT_EQUAL(table.elems[5], { "23", 2 });
    EXPECT_EQUAL(table.elems[6], {  "3", 3 });
    EXPECT_EQUAL(table.elems[7], {  "5", 2 });
    EXPECT_EQUAL(table.elems[8], {  "6", 2 });
    EXPECT_EQUAL(table.elems[9].distance, RobinHoodHashTable::EMPTY_SLOT);

    EXPECT_EQUAL(table.size(), 8);

    /* 插入 0 和 10。这会触发一连串位移，最终如下：
     *
     *   0 10 11 21  1 23  3 13  5  6
     *   0  1  1  2  3  2  3  4  3  3
     *
     *  注意，1 已跃迁到哈希到以下位置的元素范围末尾
     *  槽位 1，且 13 也跃迁到了其范围末尾。
     */
    EXPECT(table.insert("0"));
    EXPECT(table.insert("10"));

    EXPECT_EQUAL(table.elems[0], {  "0", 0 });
    EXPECT_EQUAL(table.elems[1], { "10", 1 });
    EXPECT_EQUAL(table.elems[2], { "11", 1 });
    EXPECT_EQUAL(table.elems[3], { "21", 2 });
    EXPECT_EQUAL(table.elems[4], {  "1", 3 });
    EXPECT_EQUAL(table.elems[5], { "23", 2 });
    EXPECT_EQUAL(table.elems[6], {  "3", 3 });
    EXPECT_EQUAL(table.elems[7], { "13", 4 });
    EXPECT_EQUAL(table.elems[8], {  "5", 3 });
    EXPECT_EQUAL(table.elems[9], {  "6", 3 });

    EXPECT_EQUAL(table.size(), 10);

}

PROVIDED_TEST("Wraps around the end of the table.") {
    /* 所有内容都进入槽位 7。这是仅用于测试的糟糕哈希函数
     * 用于测试。
     */
    RobinHoodHashTable table(Hash::constant(10, 7));

    /* 插入一批值。 */
    Vector<string> toAdd = {
        "H", "He", "Li", "Be", "B", "C", "N"
    };
    Vector<string> toNotAdd = {
        "O", "F", "Ne"
    };

    /* 添加这些元素。 */
    for (string elem: toAdd) {
        EXPECT(table.insert(elem));
    }

    /* 表格应如下所示：
     *
     *   Be B  C  N  .  .  .  H He Li
     *   3  4  5  6           0  1  2
     */
    EXPECT_EQUAL(table.elems[0], { "Be", 3 });
    EXPECT_EQUAL(table.elems[1], { "B",  4 });
    EXPECT_EQUAL(table.elems[2], { "C",  5 });
    EXPECT_EQUAL(table.elems[3], { "N",  6 });
    EXPECT_EQUAL(table.elems[4].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[5].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[6].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[7], { "H",  0 });
    EXPECT_EQUAL(table.elems[8], { "He", 1 });
    EXPECT_EQUAL(table.elems[9], { "Li", 2 });

    /* 确认它们全部存在。 */
    for (string elem: toAdd) {
        EXPECT(table.contains(elem));
    }

    /* 确认其他项不存在。 */
    for (string elem: toNotAdd) {
        EXPECT(!table.contains(elem));
    }
}

PROVIDED_TEST("Displacements wrap around the end of the table.") {
    /* 每个数字哈希到其最后一位。 */
    RobinHoodHashTable table(Hash::identity(10));

    /* 插入一些初始值以得到此表：
     *
     *     0  1  .  .  .  .  .  .  8  9
     *     0  0                    0  0
     */
    EXPECT(table.insert("8"));
    EXPECT(table.insert("9"));
    EXPECT(table.insert("0"));
    EXPECT(table.insert("1"));
    EXPECT_EQUAL(table.size(), 4);

    EXPECT_EQUAL(table.elems[0], { "0",  0 });
    EXPECT_EQUAL(table.elems[1], { "1",  0 });
    EXPECT_EQUAL(table.elems[2].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[3].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[4].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[5].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[6].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[7].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[8], { "8",  0 });
    EXPECT_EQUAL(table.elems[9], { "9",  0 });

    /* 插入 19。它应绕回开头，结果如下：
     *
     *     19 0  1  .  .  .  .  .  8  9
     *     1  1  1                 0  0
     */
    EXPECT(table.insert("19"));
    EXPECT_EQUAL(table.size(), 5);

    EXPECT_EQUAL(table.elems[0], { "19", 1 });
    EXPECT_EQUAL(table.elems[1], { "0",  1 });
    EXPECT_EQUAL(table.elems[2], { "1",  1 });
    EXPECT_EQUAL(table.elems[3].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[4].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[5].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[6].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[7].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[8], { "8",  0 });
    EXPECT_EQUAL(table.elems[9], { "9",  0 });

    /* 插入 18。它应绕回开头，结果如下：
     *
     *     19 9  0  1  .  .  .  .  8  18
     *     1  2  2  2              0  1
     *
     * 为什么 9 现在应位于 19 之后？因为我们只移位一个
     * 如果某元素严格比我们更接近原位，则选择该元素。9 和 19 都
     * 到家的距离相同而并列，因此当我们比较 9
     * 在移动过程中遇到 19 时，应将该 19 留在原位。
     */
    EXPECT(table.insert("18"));
    EXPECT_EQUAL(table.size(), 6);

    EXPECT_EQUAL(table.elems[0], { "19", 1 });
    EXPECT_EQUAL(table.elems[1], { "9",  2 });
    EXPECT_EQUAL(table.elems[2], { "0",  2 });
    EXPECT_EQUAL(table.elems[3], { "1",  2 });
    EXPECT_EQUAL(table.elems[4].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[5].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[6].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[7].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[8], { "8",  0 });
    EXPECT_EQUAL(table.elems[9], { "18", 1 });

    /* 插入 10。结果应如下：
     *
     *     19 9  0 10  1  .  .  .  8  18
     *     1  2  2  3  3           0  1
     */
    EXPECT(table.insert("10"));
    EXPECT_EQUAL(table.size(), 7);

    EXPECT_EQUAL(table.elems[0], { "19", 1 });
    EXPECT_EQUAL(table.elems[1], {  "9", 2 });
    EXPECT_EQUAL(table.elems[2], {  "0", 2 });
    EXPECT_EQUAL(table.elems[3], { "10", 3 });
    EXPECT_EQUAL(table.elems[4], {  "1", 3 });
    EXPECT_EQUAL(table.elems[5].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[6].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[7].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[8], { "8",  0 });
    EXPECT_EQUAL(table.elems[9], { "18", 1 });

    /* 依次插入 6、16、26。这会进行一系列绕回位移
     * 产生下表：
     *
     *     8  9 19 10  0  1  6 16  26 18
     *     2  2  3  3  4  4  0  1  2  1
     *
     * 注意，每段相同哈希值范围中的第一个元素都已经“跃过”
     * 移到范围后端。
     */
    EXPECT(table.insert("6"));
    EXPECT(table.insert("16"));
    EXPECT(table.insert("26"));

    EXPECT_EQUAL(table.elems[0], {  "8", 2 });
    EXPECT_EQUAL(table.elems[1], {  "9", 2 });
    EXPECT_EQUAL(table.elems[2], { "19", 3 });
    EXPECT_EQUAL(table.elems[3], { "10", 3 });
    EXPECT_EQUAL(table.elems[4], {  "0", 4 });
    EXPECT_EQUAL(table.elems[5], {  "1", 4 });
    EXPECT_EQUAL(table.elems[6], {  "6", 0 });
    EXPECT_EQUAL(table.elems[7], { "16", 1 });
    EXPECT_EQUAL(table.elems[8], { "26", 2 });
    EXPECT_EQUAL(table.elems[9], { "18", 1 });

    EXPECT_EQUAL(table.size(), 10);

    EXPECT(table.contains("8"));
    EXPECT(table.contains("9"));
    EXPECT(table.contains("0"));
    EXPECT(table.contains("1"));
    EXPECT(table.contains("19"));
    EXPECT(table.contains("18"));
    EXPECT(table.contains("10"));
    EXPECT(table.contains("6"));
    EXPECT(table.contains("16"));
    EXPECT(table.contains("26"));
}

PROVIDED_TEST("Doesn't allow for duplicates.") {
    /* 为保持一致，将所有内容放入槽位 0。 */
    RobinHoodHashTable table(Hash::zero(10));

    EXPECT(table.insert("dikdik"));
    EXPECT_EQUAL(table.size(), 1);

    EXPECT_EQUAL(table.elems[0], { "dikdik", 0 });
    for (int i = 1; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].distance, RobinHoodHashTable::EMPTY_SLOT);
    }

    /* 插入同一个值，次数超过表的容量。 */
    for (int i = 0; i < 100; i++) {
        EXPECT(!table.insert("dikdik"));
        EXPECT_EQUAL(table.size(), 1);

        EXPECT_EQUAL(table.elems[0], { "dikdik", 0 });
        for (int i = 1; i < 10; i++) {
            EXPECT_EQUAL(table.elems[i].distance, RobinHoodHashTable::EMPTY_SLOT);
        }
    }
}

PROVIDED_TEST("Handles inserting the empty string.") {
    RobinHoodHashTable table(Hash::zero(10));

    EXPECT(!table.contains(""));
    EXPECT(table.insert(""));

    EXPECT_EQUAL(table.elems[0], { "", 0 });
    for (int i = 1; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].distance, RobinHoodHashTable::EMPTY_SLOT);
    }

    EXPECT(table.contains(""));
    EXPECT_EQUAL(table.size(), 1);
}

PROVIDED_TEST("Lookups work even if the table is full.") {
    /* 将所有内容放入桶 7。这是很差的哈希函数，但
     * 对测试很有用。
     */
    RobinHoodHashTable table(Hash::constant(10, 7));

    /* 填充该表。 */
    for (int i = 0; i < 10; i++) {
        EXPECT(table.insert(to_string(i)));
    }
    EXPECT_EQUAL(table.size(), 10);

    /* 验证该表。 */
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(table.elems[(i + 7) % 10], { to_string(i), i });
    }

    /* 搜索所有已存在的项目。 */
    for (int i = 0; i < 10; i++) {
        EXPECT(table.contains(to_string(i)));
    }

    /* 确认不存在的元素不会出现。注意！此边界
     * 若未预先考虑，此情况可能导致代码卡住。
     */
    for (int i = 10; i < 20; i++) {
        EXPECT(!table.contains(to_string(i)));
    }
}

PROVIDED_TEST("Won't insert elements if table is full.") {
    /* 将所有内容放入槽位 7 的糟糕哈希函数。 */
    RobinHoodHashTable table(Hash::constant(10, 7));

    /* 加载该表。 */
    for (int i = 0; i < 10; i++) {
        EXPECT(table.insert(to_string(i))); // 应当成功
    }
    EXPECT_EQUAL(table.size(), 10);

    /* 验证该表。 */
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(table.elems[(i + 7) % 10], { to_string(i), i });
    }

    /* 所有这些操作都应失败。 */
    for (int i = 10; i < 20; i++) {
        EXPECT(!table.insert(to_string(i)));
    }
}

PROVIDED_TEST("Stress Test: Searches cut off early (should take at most five seconds)") {
    /* 我们将用大量元素块填满一个巨大表格，然后尝试执行
     * 查找。使用普通线性探测时，表会因以下原因陷入停顿
     * 已满。使用 Robin Hood 哈希时，这应极快终止。
     *
     * 表格通常如下所示：
     *
     * |--- 哈希码为 0 的块 ---| |--- 哈希码为 1 的块 ---| |--- 哈希码为 2 的块 ---| ...
     *
     * 如果查找某个元素，绝不应越过块末尾，因为
     * 一旦到达下一个块的开头，正在扫描的元素就会
     * 比块起始处的元素离原位更远。
     */
    const int kElemsPerBlock = 5;
    const int kNumBlocks     = 50000;
    const int kNumElems      = kNumBlocks * kElemsPerBlock;

    /* 每个元素的位置由其值对表大小取模决定。 */
    RobinHoodHashTable table(Hash::identity(kNumElems));

    /* 用具有相同哈希码的许多值块填充该表。 */
    for (int block = 0; block < kNumBlocks; block++) {
        for (int elem = 0; elem < kElemsPerBlock; elem++) {
            /* 这些值都应落入由块索引给定的位置
             * 乘以每个元素的块数。
             */
            int value = block * kElemsPerBlock + elem * kNumElems;
            EXPECT(table.insert(to_string(value)));
        }
    }
    EXPECT_EQUAL(table.size(), kNumElems);

    /* 验证该表。 */
    for (int block = 0; block < kNumBlocks; block++) {
        for (int elem = 0; elem < kElemsPerBlock; elem++) {
            int value = block * kElemsPerBlock + elem * kNumElems;
            int index = block * kElemsPerBlock + elem;
            EXPECT_EQUAL(table.elems[index], { to_string(value), elem });
        }
    }

    /* 确认每个元素都存在。由于每个块都很小，这应当非常快
     * 较小，并且块内所有元素都靠近块起始处。
     */
    for (int block = 0; block < kNumBlocks; block++) {
        for (int elem = 0; elem < kElemsPerBlock; elem++) {
            /* 这些值都应落入由块索引给定的位置
             * 乘以每个元素的块数。
             */
            int value = block * kElemsPerBlock + elem * kNumElems;
            EXPECT(table.contains(to_string(value)));
        }
    }

    /* 现在，尝试查找一批不存在的值。每次搜索
     * 搜索某个值应快速终止，因为一旦扫描超过
     * 一个块时，当前扫描元素的距离值将重置为
     * 零，搜索即可停止。
     *
     * 另一方面，如果搜索过程执行标准线性探测
     * 如果采用扫描直到找到空槽的方法，则必须扫描所有
     * 对表中的每个位置遍历表中所有位置，这将花费
     * 耗时长到无法在任何合理时间内完成。
     */
    for (int block = 0; block < kNumBlocks; block++) {
        for (int elem = kElemsPerBlock; elem < 2 * kElemsPerBlock; elem++) {
            /* 这些值都应落入由块索引给定的位置
             * 乘以每个元素的块数。
             */
            int value = block * kElemsPerBlock + elem * kNumElems;
            EXPECT(!table.contains(to_string(value)));
        }
    }
}

PROVIDED_TEST("Stress Test: Handles pure insertion of elements (should take at most three seconds).") {
    const int kNumTrials = 50; // 重复多次，以暴露可能潜藏的任何错误。
    for (int trial = 0; trial < kNumTrials; trial++) {
        RobinHoodHashTable table(Hash::random(100));

        const int kNumElems = 75;
        for (int i = 0; i < kNumElems; i++) {
            /* 确认此时仅存在正确的元素。 */
            for (int j = 0; j < kNumElems; j++) {
                EXPECT_EQUAL(table.contains(to_string(j)), j < i);
            }

            /* 添加元素。 */
            EXPECT(table.insert(to_string(i))); // 应当成功
            EXPECT_EQUAL(table.size(), i + 1);
        }
    }
}

PROVIDED_TEST("Stress Test: Inserts/searches work in expected time O(1) (should take at most three seconds).") {
    /* 大量槽位。 */
    const int kNumSlots = 1000000;

    /* 使用随机哈希函数创建一个巨大的哈希表。 */
    RobinHoodHashTable table(Hash::random(kNumSlots));

    /* 在表中搜索大量元素。这应该很快，因为
     * 该表为空。
     */
    for (int i = 0; i < kNumSlots; i++) {
        EXPECT(!table.contains(to_string(i)));
    }

    /* 插入大量元素。 */
    const int kLotsOfElems = 100000; // 10% 的负载因子——非常小！
    for (int i = 0; i < kLotsOfElems; i++) {
        EXPECT(table.insert(to_string(i)));
    }
    for (int i = 0; i < kLotsOfElems; i++) {
        EXPECT(table.contains(to_string(i)));
    }

    /* 确认其他元素不存在。这些失败查找仍应很快
     * 因为负载因子较低。
     */
    for (int i = kLotsOfElems; i < 2 * kLotsOfElems; i++) {
        EXPECT(!table.contains(to_string(i)));
    }
}

PROVIDED_TEST("Can insert and remove a single element.") {
    /* 所有内容都哈希到零。这是一个*糟糕透顶*的哈希函数，仅用于
     * 仅用于测试。
     */
    RobinHoodHashTable table(Hash::zero(200));

    /* 插入一个元素。 */
    EXPECT(table.insert("137"));
    EXPECT_EQUAL(table.size(), 1);
    EXPECT(!table.isEmpty());

    /* 验证表的内部状态。 */
    EXPECT_EQUAL(table.elems[0], { "137", 0 });
    for (int i = 1; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].distance, RobinHoodHashTable::EMPTY_SLOT);
    }

    /* 移除该元素。 */
    EXPECT(table.remove("137"));
    EXPECT_EQUAL(table.size(), 0);
    EXPECT(table.isEmpty());

    /* 验证表的内部状态。 */
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].distance, RobinHoodHashTable::EMPTY_SLOT);
    }

    EXPECT(!table.contains("137"));
}

PROVIDED_TEST("Handles removing the empty string.") {
    RobinHoodHashTable table(Hash::zero(10));

    /* 我们不应能从表中移除空字符串；
     * 它不在那里。
     */
    EXPECT(!table.contains(""));
    EXPECT(!table.remove(""));

    /* 添加空字符串。 */
    EXPECT(table.insert(""));

    /* 验证表的内部状态。 */
    EXPECT_EQUAL(table.elems[0], { "", 0 });
    for (int i = 1; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].distance, RobinHoodHashTable::EMPTY_SLOT);
    }

    EXPECT(table.contains(""));
    EXPECT_EQUAL(table.size(), 1);

    /* 删除空字符串。 */
    EXPECT(table.remove(""));
    EXPECT_EQUAL(table.size(), 0);
    EXPECT(!table.contains(""));

    /* 验证表的内部状态。 */
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].distance, RobinHoodHashTable::EMPTY_SLOT);
    }

    EXPECT(!table.remove(""));
}

PROVIDED_TEST("Doesn't backward-shift elements from their homes.") {
    /* 每个元素哈希到其自身数值，再对表大小取模。 */
    RobinHoodHashTable table(Hash::identity(10));

    /* 插入两段相邻的值，得到此序列：
     *
     * .  1 11 21 31  5 15 25 35 .
     *    0  1  2  3  0  1  2  3
     */
    EXPECT(table.insert("1"));
    EXPECT(table.insert("11"));
    EXPECT(table.insert("21"));
    EXPECT(table.insert("31"));
    EXPECT(table.insert("5"));
    EXPECT(table.insert("15"));
    EXPECT(table.insert("25"));
    EXPECT(table.insert("35"));
    EXPECT_EQUAL(table.size(), 8);

    /* 验证表的内部状态。 */
    EXPECT_EQUAL(table.elems[0].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[1], {  "1", 0 });
    EXPECT_EQUAL(table.elems[2], { "11", 1 });
    EXPECT_EQUAL(table.elems[3], { "21", 2 });
    EXPECT_EQUAL(table.elems[4], { "31", 3 });
    EXPECT_EQUAL(table.elems[5], {  "5", 0 });
    EXPECT_EQUAL(table.elems[6], { "15", 1 });
    EXPECT_EQUAL(table.elems[7], { "25", 2 });
    EXPECT_EQUAL(table.elems[8], { "35", 3 });
    EXPECT_EQUAL(table.elems[9].distance, RobinHoodHashTable::EMPTY_SLOT);

    /* 删除 11。应通过后移删除得到
     *
     * .  1 21 31  .  5 15 25 35 .
     *    0  1  2     0  1  2  3
     */
    EXPECT(table.remove("11"));
    EXPECT_EQUAL(table.size(), 7);

    EXPECT_EQUAL(table.elems[0].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[1], {  "1", 0 });
    EXPECT_EQUAL(table.elems[2], { "21", 1 });
    EXPECT_EQUAL(table.elems[3], { "31", 2 });
    EXPECT_EQUAL(table.elems[4].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[5], {  "5", 0 });
    EXPECT_EQUAL(table.elems[6], { "15", 1 });
    EXPECT_EQUAL(table.elems[7], { "25", 2 });
    EXPECT_EQUAL(table.elems[8], { "35", 3 });
    EXPECT_EQUAL(table.elems[9].distance, RobinHoodHashTable::EMPTY_SLOT);

    EXPECT(table.contains("1"));
    EXPECT(!table.contains("11"));
    EXPECT(table.contains("21"));
    EXPECT(table.contains("31"));
    EXPECT(table.contains("5"));
    EXPECT(table.contains("15"));
    EXPECT(table.contains("25"));
    EXPECT(table.contains("35"));
}

PROVIDED_TEST("Deletes around the end of the table.") {
    /* 所有内容都放入槽位 8。 */
    RobinHoodHashTable table(Hash::constant(10, 8));

    /* 插入五个值，恢复为此表：
     *
     * 2  3  4  .  .  .  .  .  0  1
     * 2  3  4                 0  1
     */
    for (int i = 0; i < 5; i++) {
        EXPECT(table.insert(to_string(i)));
    }
    EXPECT_EQUAL(table.size(), 5);

    EXPECT_EQUAL(table.elems[0], {  "2", 2 });
    EXPECT_EQUAL(table.elems[1], {  "3", 3 });
    EXPECT_EQUAL(table.elems[2], {  "4", 4 });
    EXPECT_EQUAL(table.elems[3].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[4].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[5].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[6].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[7].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[8], {  "0", 0 });
    EXPECT_EQUAL(table.elems[9], {  "1", 1 });

    /* 删除 0。所有内容应像这样向后移动：
     *
     * 3  4  .  .  .  .  .  .  1  2
     * 2  3                    0  1
     */
    EXPECT(table.remove("0"));
    EXPECT_EQUAL(table.size(), 4);

    EXPECT_EQUAL(table.elems[0], {  "3", 2 });
    EXPECT_EQUAL(table.elems[1], {  "4", 3 });
    EXPECT_EQUAL(table.elems[2].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[3].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[4].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[5].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[6].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[7].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[8], {  "1", 0 });
    EXPECT_EQUAL(table.elems[9], {  "2", 1 });

    /* 删除 1。所有内容应像这样向后移动：
     *
     * 4  .  .  .  .  .  .  .  2  3
     * 2                       0  1
     */
    EXPECT(table.remove("1"));
    EXPECT_EQUAL(table.size(), 3);

    EXPECT_EQUAL(table.elems[0], {  "4", 2 });
    EXPECT_EQUAL(table.elems[1].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[2].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[3].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[4].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[5].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[6].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[7].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[8], {  "2", 0 });
    EXPECT_EQUAL(table.elems[9], {  "3", 1 });

    /* 删除 2。所有内容应像这样向后移动：
     *
     * .  .  .  .  .  .  .  .  3  4
     *                         0  1
     */
    EXPECT(table.remove("2"));
    EXPECT_EQUAL(table.size(), 2);

    EXPECT_EQUAL(table.elems[0].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[1].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[2].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[3].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[4].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[5].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[6].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[7].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[8], {  "3", 0 });
    EXPECT_EQUAL(table.elems[9], {  "4", 1 });

    /* 删除 3。所有内容应像这样向后移动：
     *
     * .  .  .  .  .  .  .  .  4  .
     *                         0
     */
    EXPECT(table.remove("3"));
    EXPECT_EQUAL(table.size(), 1);

    EXPECT_EQUAL(table.elems[0].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[1].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[2].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[3].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[4].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[5].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[6].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[7].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[8], {  "4", 0 });
    EXPECT_EQUAL(table.elems[9].distance, RobinHoodHashTable::EMPTY_SLOT);

    /* 删除 4。此时表应为空。 */
    EXPECT(table.remove("4"));
    EXPECT_EQUAL(table.size(), 0);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].distance, RobinHoodHashTable::EMPTY_SLOT);
    }
}

PROVIDED_TEST("Removing non-existent elements has no effect.") {
    /* 将所有内容放入桶 0，这是一个糟糕的哈希函数选择，但
     * 这会使测试容易得多。
     */
    RobinHoodHashTable table(Hash::zero(10));

    /* 填充该表。 */
    for (int i = 0; i < 5; i++) {
        EXPECT(table.insert(to_string(i)));
    }
    EXPECT_EQUAL(table.size(), 5);

    /* 验证表的内部结构。我们应看到：
     *
     * 0 1 2 3 4 . . . . .
     * 0 1 2 3 4
     */
    EXPECT_EQUAL(table.size(), 5);
    EXPECT_EQUAL(table.elems[0], {  "0", 0 });
    EXPECT_EQUAL(table.elems[1], {  "1", 1 });
    EXPECT_EQUAL(table.elems[2], {  "2", 2 });
    EXPECT_EQUAL(table.elems[3], {  "3", 3 });
    EXPECT_EQUAL(table.elems[4], {  "4", 4 });
    EXPECT_EQUAL(table.elems[5].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[6].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[7].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[8].distance, RobinHoodHashTable::EMPTY_SLOT);
    EXPECT_EQUAL(table.elems[9].distance, RobinHoodHashTable::EMPTY_SLOT);

    /* 尝试移除不存在的内容。 */
    for (int i = 5; i < 30; i++) {
        EXPECT(!table.remove(to_string(i)));

        /* 确认表未发生变化。 */
        EXPECT_EQUAL(table.size(), 5);
        EXPECT_EQUAL(table.elems[0], {  "0", 0 });
        EXPECT_EQUAL(table.elems[1], {  "1", 1 });
        EXPECT_EQUAL(table.elems[2], {  "2", 2 });
        EXPECT_EQUAL(table.elems[3], {  "3", 3 });
        EXPECT_EQUAL(table.elems[4], {  "4", 4 });
        EXPECT_EQUAL(table.elems[5].distance, RobinHoodHashTable::EMPTY_SLOT);
        EXPECT_EQUAL(table.elems[6].distance, RobinHoodHashTable::EMPTY_SLOT);
        EXPECT_EQUAL(table.elems[7].distance, RobinHoodHashTable::EMPTY_SLOT);
        EXPECT_EQUAL(table.elems[8].distance, RobinHoodHashTable::EMPTY_SLOT);
        EXPECT_EQUAL(table.elems[9].distance, RobinHoodHashTable::EMPTY_SLOT);
    }
}

PROVIDED_TEST("Can remove from a full table.") {
    /* 将所有内容放入桶 7；这是很差的哈希函数选择，但
     * 这会使测试容易得多。
     */
    RobinHoodHashTable table(Hash::constant(10, 7));

    /* 填充该表。 */
    for (int i = 0; i < 10; i++) {
        EXPECT(table.insert(to_string(i)));
    }
    EXPECT_EQUAL(table.size(), 10);

    /* 验证表的内部结构。我们应看到：
     *
     * 3  4  5  6  7  8  9  0  1  2
     * 3  4  5  6  7  8  9  0  1  2
     */
    EXPECT_EQUAL(table.size(), 10);
    EXPECT_EQUAL(table.elems[0], {  "3", 3 });
    EXPECT_EQUAL(table.elems[1], {  "4", 4 });
    EXPECT_EQUAL(table.elems[2], {  "5", 5 });
    EXPECT_EQUAL(table.elems[3], {  "6", 6 });
    EXPECT_EQUAL(table.elems[4], {  "7", 7 });
    EXPECT_EQUAL(table.elems[5], {  "8", 8 });
    EXPECT_EQUAL(table.elems[6], {  "9", 9 });
    EXPECT_EQUAL(table.elems[7], {  "0", 0 });
    EXPECT_EQUAL(table.elems[8], {  "1", 1 });
    EXPECT_EQUAL(table.elems[9], {  "2", 2 });

    /* 尝试移除一些不存在的元素。如果你的实现有问题，这可能会挂起
     * remove 的实现没有预料到这种情况。
     */
    for (int i = 10; i < 20; i++) {
        EXPECT(!table.remove(to_string(i)));

        /* 确保表保持不变。 */
        EXPECT_EQUAL(table.size(), 10);

        EXPECT_EQUAL(table.elems[0], {  "3", 3 });
        EXPECT_EQUAL(table.elems[1], {  "4", 4 });
        EXPECT_EQUAL(table.elems[2], {  "5", 5 });
        EXPECT_EQUAL(table.elems[3], {  "6", 6 });
        EXPECT_EQUAL(table.elems[4], {  "7", 7 });
        EXPECT_EQUAL(table.elems[5], {  "8", 8 });
        EXPECT_EQUAL(table.elems[6], {  "9", 9 });
        EXPECT_EQUAL(table.elems[7], {  "0", 0 });
        EXPECT_EQUAL(table.elems[8], {  "1", 1 });
        EXPECT_EQUAL(table.elems[9], {  "2", 2 });
    }

    /* 现在执行实际移除操作。 */
    for (int i = 0; i < 10; i++) {
        EXPECT(table.remove(to_string(i)));
    }

    EXPECT(table.isEmpty());
    EXPECT_EQUAL(table.size(), 0);

    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].distance, RobinHoodHashTable::EMPTY_SLOT);
    }
}

PROVIDED_TEST("Stress Test: Handles large numbers of removals (should take under a second).") {
    const int kNumTrials = 50; // 重复多次，以暴露可能潜藏的任何错误。
    for (int trial = 0; trial < kNumTrials; trial++) {
        RobinHoodHashTable table(Hash::random(100));

        const int kNumElems = 75;
        for (int i = 0; i < kNumElems; i++) {
            table.insert(to_string(i));
        }

        EXPECT_EQUAL(table.size(), kNumElems);

        for (int i = 0; i < kNumElems; i++) {
            /* 确认此时仅存在正确的元素。 */
            for (int j = 0; j < kNumElems; j++) {
                EXPECT_EQUAL(table.contains(to_string(j)), j >= i);
            }

            EXPECT(table.remove(to_string(i)));
            EXPECT_EQUAL(table.size(), kNumElems - i - 1);
        }
    }
}

PROVIDED_TEST("Stress Test: Inserts/searches/deletes work in expected time O(1).") {
    /* 大量槽位。 */
    const int kNumSlots = 1000000;

    /* 使用随机哈希函数创建一个巨大的哈希表。 */
    RobinHoodHashTable table(Hash::random(kNumSlots));

    /* 插入大量元素。 */
    const int kLotsOfElems = 100000; // 10% 的负载因子——非常小！
    for (int i = 0; i < kLotsOfElems; i++) {
        EXPECT(table.insert(to_string(i)));
    }

    /* 移除其中间一半。 */
    for (int i = kLotsOfElems / 4; i < 3 * kLotsOfElems / 4; i++) {
        EXPECT(table.remove(to_string(i)));
    }

    /* 搜索大量元素，并确认应该存在的元素
     * 确实存在。
     */
    for (int i = 0; i < kLotsOfElems; i++) {
        EXPECT_EQUAL(table.contains(to_string(i)), bool(i < kLotsOfElems / 4 || i >= 3 * kLotsOfElems / 4));
    }
}

#include "filelib.h"
#include "Demos/Timer.h"
#include <fstream>
PROVIDED_TEST("Stress Test: Handles large workflows with little free space (should take at most five seconds)") {
    SHOW_ERROR("Stress test is disabled by default. To run it, comment out line " + to_string(__LINE__) + " of " + getTail(__FILE__) + ".");

    Vector<string> english;
    ifstream input("res/EnglishWords.txt");

    for (string word; getline(input, word); ) {
        english += word;
    }

    /* 负载因子 0.99。 */
    Timing::Timer timer;
    timer.start();
    RobinHoodHashTable table(Hash::consistentRandom(english.size() / 0.99));

    /* 插入所有内容。 */
    for (const string& word: english) {
        EXPECT(table.insert(word));
    }
    EXPECT_EQUAL(table.size(), english.size());

    /* 确保所有内容都存在，并且其大写版本不存在。 */
    for (const string& word: english) {
        EXPECT(table.contains(word));
        EXPECT(!table.contains(toUpperCase(word)));
    }

    /* 移除所有内容，并额外尝试移除一些不存在的内容。 */
    for (const string& word: english) {
        EXPECT(table.remove(word));
        EXPECT(!table.contains(word));
        EXPECT(!table.remove(toUpperCase(word)));
    }

    EXPECT_EQUAL(table.size(), 0);
    EXPECT(table.isEmpty());

    timer.stop();
    EXPECT_LESS_THAN(timer.elapsed(), 5e9); // 单位为纳秒
}
