#include "LinearProbingHashTable.h"
using namespace std;

LinearProbingHashTable::LinearProbingHashTable(HashFunction<string> hashFn) {
    /* TODO：删除此注释及下一行，然后实现此函数。 */
    (void) hashFn;
}

LinearProbingHashTable::~LinearProbingHashTable() {
    /* TODO：删除此注释，然后实现此函数。 */
}

int LinearProbingHashTable::size() const {
    /* TODO：删除此注释及接下来的几行，然后实现此函数。 */
    return -1;
}

bool LinearProbingHashTable::isEmpty() const {
    /* TODO：删除此注释及接下来的几行，然后实现此函数。 */
    return false;
}

bool LinearProbingHashTable::insert(const string& elem) {
    /* TODO：删除此注释及接下来的几行，然后实现此函数。 */
    (void) elem;
    return false;
}

bool LinearProbingHashTable::contains(const string& elem) const {
    /* TODO：删除此注释及接下来的几行，然后实现此函数。 */
    (void) elem;
    return false;
}

bool LinearProbingHashTable::remove(const string& elem) {
    /* TODO：删除此注释及接下来的几行，然后实现此函数。 */
    (void) elem;
    return false;
}

void LinearProbingHashTable::printDebugInfo() const {
    /* TODO：删除此注释并实现此函数。 */
}


/* * * * * * 此处以下为测试用例 * * * * * */
#include "GUI/SimpleTest.h"

/* 可选：在此添加你自己的自定义测试！ */














/* * * * * 此处以下为提供的测试 * * * * */
#include "vector.h"

PROVIDED_TEST("Table is initially empty.") {
    LinearProbingHashTable table(Hash::random(10));

    /* 检查外部接口以确保其外观正确。 */
    EXPECT_EQUAL(table.size(), 0);
    EXPECT(table.isEmpty());

    /* 检查内部是否一切正常。 */
    EXPECT_NOT_EQUAL(table.elems, nullptr);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].type, LinearProbingHashTable::SlotType::EMPTY);
    }
}

PROVIDED_TEST("Can insert and look up a single value.") {
    LinearProbingHashTable table(Hash::identity(10));

    EXPECT(!table.contains("0"));
    EXPECT(table.insert("0"));
    EXPECT(table.contains("0"));

    /* 检查内部表示。 */
    EXPECT_EQUAL(table.elems[0], { "0", LinearProbingHashTable::SlotType::FILLED });
    for (int i = 1; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].type, LinearProbingHashTable::SlotType::EMPTY);
    }
}

PROVIDED_TEST("Is case-sensitive.") {
    LinearProbingHashTable table(Hash::zero(10));

    EXPECT(!table.contains("a"));
    EXPECT(!table.contains("A"));
    EXPECT(table.insert("a"));

    /* 第一个槽位应包含 'a'，其余槽位应为空。 */
    EXPECT_EQUAL(table.elems[0], { "a", LinearProbingHashTable::SlotType::FILLED });
    for (int i = 1; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].type, LinearProbingHashTable::SlotType::EMPTY);
    }

    EXPECT(table.contains("a"));
    EXPECT(!table.contains("A"));
}

PROVIDED_TEST("Insertions/lookups work with hash collisions.") {
    /* 使用一个非常、非常糟糕的哈希函数，将所有内容都映射到槽位零。 */
    LinearProbingHashTable table(Hash::zero(10));

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

    /* 应为 'Quokka'、'Pudu'、'Gerenuk'、'Dikdik'，后跟六个空槽位。 */
    for (int i = 0; i < 10; i++) {
        if (i < toAdd.size()) {
            EXPECT_EQUAL(table.elems[i], { toAdd[i], LinearProbingHashTable::SlotType::FILLED });
        } else {
            EXPECT_EQUAL(table.elems[i].type, LinearProbingHashTable::SlotType::EMPTY);
        }
    }

    for (string animal: toAdd) {
        EXPECT(table.contains(animal));
    }
    for (string animal: toNotAdd) {
        EXPECT(!table.contains(animal));
    }
}

PROVIDED_TEST("Insertions/lookups succeed when ranges overlap.") {
    /* 所用哈希函数将字符串映射到其数值。这使我们能够
     * 使我们能够控制哈希表内容。
     */
    LinearProbingHashTable table(Hash::identity(10));

    /* 放入 0 和 10。此时该表应如下所示：
     *
     *            0 10 . . . . . . . .
     *
     */
    EXPECT(table.insert("0"));
    EXPECT(table.insert("10"));
    EXPECT(table.contains("0"));
    EXPECT(table.contains("10"));

    EXPECT_EQUAL(table.elems[0], {  "0", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[1], { "10", LinearProbingHashTable::SlotType::FILLED });
    for (int i = 2; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].type, LinearProbingHashTable::SlotType::EMPTY);
    }

    /* 现在插入值 1、2、3、4 和 5。该表应如下所示：
     * 如下所示：
     *
     *           0 10  1  2  3  4  5  .  .  .
     */
    EXPECT(table.insert("1"));
    EXPECT(table.insert("2"));
    EXPECT(table.insert("3"));
    EXPECT(table.insert("4"));
    EXPECT(table.insert("5"));

    EXPECT_EQUAL(table.elems[0], {  "0", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[1], { "10", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[2], {  "1", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[3], {  "2", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[4], {  "3", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[5], {  "4", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[6], {  "5", LinearProbingHashTable::SlotType::FILLED });
    for (int i = 7; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].type, LinearProbingHashTable::SlotType::EMPTY);
    }

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

PROVIDED_TEST("Wraps around the end of the table.") {
    /* 所有内容都进入槽位 7。这是仅用于测试的糟糕哈希函数
     * 用于测试。
     */
    LinearProbingHashTable table(Hash::constant(10, 7));

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

    /* 表格应为
     *
     * Be B  C  N  .  .  .  H  He Li
     */
    EXPECT_EQUAL(table.elems[0], { "Be", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[1], { "B",  LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[2], { "C",  LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[3], { "N",  LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[4].type,     LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[5].type,     LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[6].type,     LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[7], { "H",   LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[8], { "He",  LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[9], { "Li",  LinearProbingHashTable::SlotType::FILLED });

    /* 确认它们全部存在。 */
    for (string elem: toAdd) {
        EXPECT(table.contains(elem));
    }

    /* 确认其他项不存在。 */
    for (string elem: toNotAdd) {
        EXPECT(!table.contains(elem));
    }
}

PROVIDED_TEST("Doesn't allow for duplicates.") {
    /* 为保持一致，将所有内容放入槽位 0。 */
    LinearProbingHashTable table(Hash::zero(10));

    EXPECT(table.insert("Dikdik"));
    EXPECT_EQUAL(table.size(), 1);

    /* 插入同一个值，次数超过表的容量。 */
    for (int i = 0; i < 100; i++) {
        EXPECT(!table.insert("Dikdik"));
        EXPECT_EQUAL(table.size(), 1);
    }

    EXPECT_EQUAL(table.elems[0], { "Dikdik", LinearProbingHashTable::SlotType::FILLED });
    for (int i = 1; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].type, LinearProbingHashTable::SlotType::EMPTY);
    }
}

PROVIDED_TEST("Handles inserting the empty string.") {
    LinearProbingHashTable table(Hash::zero(10));

    EXPECT(!table.contains(""));
    EXPECT(table.insert(""));
    EXPECT(table.contains(""));
    EXPECT_EQUAL(table.size(), 1);

    EXPECT_EQUAL(table.elems[0], { "", LinearProbingHashTable::SlotType::FILLED });
    for (int i = 1; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].type, LinearProbingHashTable::SlotType::EMPTY);
    }
}

PROVIDED_TEST("Lookups work even if the table is full.") {
    /* 将所有内容放入桶 7。这是很差的哈希函数，但
     * 对测试很有用。
     */
    LinearProbingHashTable table(Hash::constant(10, 7));

    /* 填充该表。 */
    for (int i = 0; i < 10; i++) {
        EXPECT(table.insert(to_string(i)));
    }

    /* 验证该表具有预期形状。 */
    EXPECT_EQUAL(table.size(), 10);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(table.elems[(i + 7) % 10], { to_string(i), LinearProbingHashTable::SlotType::FILLED });
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
    /* 将所有内容放入槽位 0 的糟糕哈希函数。 */
    LinearProbingHashTable table(Hash::zero(10));

    /* 加载该表。 */
    for (int i = 0; i < 10; i++) {
        EXPECT(table.insert(to_string(i))); // 应当成功
    }

    /* 验证该表具有预期形状。 */
    EXPECT_EQUAL(table.size(), 10);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i], { to_string(i), LinearProbingHashTable::SlotType::FILLED });
    }

    /* 所有这些操作都应失败。 */
    for (int i = 10; i < 20; i++) {
        EXPECT(!table.insert(to_string(i)));
    }

    /* 确认表未被修改。 */
    EXPECT_EQUAL(table.size(), 10);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i], { to_string(i), LinearProbingHashTable::SlotType::FILLED });
    }
}

PROVIDED_TEST("Stress Test: Handles pure insertion of elements (should take at most three seconds).") {
    const int kNumTrials = 50; // 重复多次，以暴露可能潜藏的任何错误。
    for (int trial = 0; trial < kNumTrials; trial++) {
        LinearProbingHashTable table(Hash::random(100));

        const int kNumElems = 75;
        for (int i = 0; i < kNumElems; i++) {
            /* 确认此时仅存在正确的元素。 */
            for (int j = 0; j < kNumElems; j++) {
                EXPECT_EQUAL(table.contains(to_string(j)), bool(j < i));
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
    LinearProbingHashTable table(Hash::random(kNumSlots));

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
    /* 糟糕的哈希函数，将每个字符串映射为其表示的数字。 */
    LinearProbingHashTable table(Hash::zero(10));

    /* 插入一个元素。 */
    EXPECT(table.insert("137"));
    EXPECT_EQUAL(table.size(), 1);
    EXPECT(!table.isEmpty());

    /* 验证该表具有正确形状。 */
    EXPECT_EQUAL(table.elems[0], { "137", LinearProbingHashTable::SlotType::FILLED });
    for (int i = 1; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].type, LinearProbingHashTable::SlotType::EMPTY);
    }

    /* 移除该元素。 */
    EXPECT(table.remove("137"));
    EXPECT_EQUAL(table.size(), 0);
    EXPECT(table.isEmpty());

    /* 验证该表具有正确形状。 */
    EXPECT_EQUAL(table.elems[0].type, LinearProbingHashTable::SlotType::TOMBSTONE);
    for (int i = 1; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].type, LinearProbingHashTable::SlotType::EMPTY);
    }

    /* 确认查找失败。 */
    EXPECT(!table.contains("137"));
}

PROVIDED_TEST("Handles a single tombstone.") {
    /* 将每个项目映射到其数值位置的哈希函数，使测试
     * 可预测地控制元素放置的位置。
     */
    LinearProbingHashTable table(Hash::identity(10));

    /* 插入这些值后，表如下所示：
     *
     *  .  1  2  3 13  5  .  .  .  .
     */
    EXPECT(table.insert("1"));
    EXPECT(table.insert("2"));
    EXPECT(table.insert("3"));
    EXPECT(table.insert("13"));
    EXPECT(table.insert("5"));
    EXPECT_EQUAL(table.size(), 5);

    EXPECT_EQUAL(table.elems[0].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[1], {  "1", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[2], {  "2", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[3], {  "3", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[4], { "13", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[5], {  "5", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[6].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[7].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[8].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[9].type,    LinearProbingHashTable::SlotType::EMPTY);

    /* 从表中删除 3。现在应得到如下状态，其中 T
     * 是墓碑标记。
     *
     *    .  1  2  T 13  5  .  .  .  .
     */
    EXPECT(table.remove("3"));
    EXPECT_EQUAL(table.size(), 4);

    EXPECT_EQUAL(table.elems[0].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[1], {  "1", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[2], {  "2", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[3].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[4], { "13", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[5], {  "5", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[6].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[7].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[8].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[9].type,    LinearProbingHashTable::SlotType::EMPTY);

    /* 确认其他所有内容仍然存在。请注意，如果 13
     * 缺失时，可能没有扫描到
     * 墓碑槽位；如果缺少 5，可能意味着我们
     * 尝试将之前的元素向后拉，但这并不
     * 安全。
     */
    EXPECT(table.contains("1"));
    EXPECT(table.contains("2"));
    EXPECT(!table.contains("3"));
    EXPECT(table.contains("13"));
    EXPECT(table.contains("5"));
}

PROVIDED_TEST("Handles lookups with long chains of tombstones") {
    /* 将每个项目映射到其数值位置的哈希函数，使测试
     * 可预测地控制元素放置的位置。
     */
    LinearProbingHashTable table(Hash::identity(10));

    /* 构造此模式：
     *
     * T 1 . . 4 5 T T T T
     */
    EXPECT(table.insert("4"));
    EXPECT(table.insert("5"));
    EXPECT(table.insert("6"));
    EXPECT(table.insert("7"));
    EXPECT(table.insert("8"));
    EXPECT(table.insert("9"));
    EXPECT(table.insert("0"));
    EXPECT(table.insert("1"));
    EXPECT(table.remove("6"));
    EXPECT(table.remove("7"));
    EXPECT(table.remove("8"));
    EXPECT(table.remove("9"));
    EXPECT(table.remove("0"));

    EXPECT_EQUAL(table.elems[0].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[1], {  "1", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[2].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[3].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[4], {  "4", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[5], {  "5", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[6].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[7].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[8].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[9].type,    LinearProbingHashTable::SlotType::TOMBSTONE);

    /* 确认 1、4 和 5 存在。 */
    EXPECT(table.contains("4"));
    EXPECT(table.contains("5"));
    EXPECT(table.contains("1"));

    /* 确保没有其他内容。 */
    EXPECT(!table.contains("6"));
    EXPECT(!table.contains("7"));
    EXPECT(!table.contains("8"));
    EXPECT(!table.contains("9"));
    EXPECT(!table.contains("0"));

    EXPECT_EQUAL(table.size(), 3);
}

PROVIDED_TEST("Recycles space from tombstones.") {
    LinearProbingHashTable table(Hash::zero(10));

    /* 添加十个值。 */
    for (int i = 0; i < 10; i++) {
        EXPECT(table.insert(to_string(i)));
    }
    EXPECT_EQUAL(table.size(), 10);

    /* 删除全部。 */
    for (int i = 0; i < 10; i++) {
        EXPECT(table.remove(to_string(i)));
    }

    /* 表格现在应为空，不过每个槽位现在都是墓碑。 */
    EXPECT_EQUAL(table.size(), 0);
    EXPECT(table.isEmpty());
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].type, LinearProbingHashTable::SlotType::TOMBSTONE);
    }

    /* 再次添加这些元素。如果墓碑空间没有被回收，
     * 这些操作将失败。
     */
    for (int i = 0; i < 10; i++) {
        EXPECT(table.insert(to_string(i + 1000)));
        EXPECT_EQUAL(table.size(), i + 1);
    }

    /* 确认表具有正确形状。 */
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i], { to_string(i + 1000), LinearProbingHashTable::SlotType::FILLED });
    }

    /* 这些操作应失败，因为表格现在已满。 */
    for (int i = 10; i < 20; i++) {
        EXPECT(!table.insert(to_string(i)));
        EXPECT_EQUAL(table.size(), 10);
    }

    /* 确认前一个位没有更改表。 */
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i], { to_string(i + 1000), LinearProbingHashTable::SlotType::FILLED });
    }
}

PROVIDED_TEST("Insertions over tombstones don't add duplicates.") {
    /* 将所有内容放入槽位 4 的哈希函数。这是一个很差的哈希
     * 没人会真正使用的函数，但对测试来说非常
     * 很方便！
     */
    LinearProbingHashTable table(Hash::constant(10, 4));

    /* 构造此模式：
     *
     * T 1 . . 4 5 T T T T
     */
    EXPECT(table.insert("4"));
    EXPECT(table.insert("5"));
    EXPECT(table.insert("6"));
    EXPECT(table.insert("7"));
    EXPECT(table.insert("8"));
    EXPECT(table.insert("9"));
    EXPECT(table.insert("0"));
    EXPECT(table.insert("1"));
    EXPECT(table.remove("6"));
    EXPECT(table.remove("7"));
    EXPECT(table.remove("8"));
    EXPECT(table.remove("9"));
    EXPECT(table.remove("0"));

    EXPECT_EQUAL(table.elems[0].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[1], {  "1", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[2].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[3].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[4], {  "4", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[5], {  "5", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[6].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[7].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[8].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[9].type,    LinearProbingHashTable::SlotType::TOMBSTONE);

    /* 将 1 插入表中。元素 1 已存在，但要找到它
     * 必须跳过墓碑，即使插入操作倾向于填充
     * 墓碑。
     */
    EXPECT(!table.insert("1"));
    EXPECT_EQUAL(table.size(), 3);

    /* 再次确认上一个测试没有改变任何内容。 */
    EXPECT_EQUAL(table.elems[0].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[1], {  "1", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[2].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[3].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[4], {  "4", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[5], {  "5", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[6].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[7].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[8].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[9].type,    LinearProbingHashTable::SlotType::TOMBSTONE);

    /* 确保无法移除两个 1。 */
    EXPECT(table.remove("1"));
    EXPECT_EQUAL(table.size(), 2);

    EXPECT_EQUAL(table.elems[0].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[1].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[2].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[3].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[4], {  "4", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[5], {  "5", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[6].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[7].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[8].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[9].type,    LinearProbingHashTable::SlotType::TOMBSTONE);

    EXPECT(!table.remove("1"));
    EXPECT_EQUAL(table.size(), 2);

    EXPECT_EQUAL(table.elems[0].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[1].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[2].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[3].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[4], {  "4", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[5], {  "5", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[6].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[7].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[8].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[9].type,    LinearProbingHashTable::SlotType::TOMBSTONE);

    /* 确认 4 和 5 仍然存在。 */
    EXPECT(table.contains("4"));
    EXPECT(table.contains("5"));

    /* 确保没有其他内容。 */
    EXPECT(!table.contains("6"));
    EXPECT(!table.contains("7"));
    EXPECT(!table.contains("8"));
    EXPECT(!table.contains("9"));
    EXPECT(!table.contains("0"));
}

PROVIDED_TEST("Handles removing the empty string.") {
    LinearProbingHashTable table(Hash::random(10));

    EXPECT(!table.remove(""));

    EXPECT(!table.contains(""));
    EXPECT(table.insert(""));
    EXPECT(table.contains(""));
    EXPECT_EQUAL(table.size(), 1);

    EXPECT(table.remove(""));
    EXPECT_EQUAL(table.size(), 0);
    EXPECT(!table.contains(""));

    EXPECT(!table.remove(""));
}

PROVIDED_TEST("Can remove from a full table.") {
    /* 将所有内容放入桶 7；这是很差的哈希函数选择，但
     * 这会使测试容易得多。
     */
    LinearProbingHashTable table(Hash::constant(10, 7));

    /* 填充该表。 */
    for (int i = 0; i < 10; i++) {
        EXPECT(table.insert(to_string(i)));
    }
    EXPECT_EQUAL(table.size(), 10);

    /* 验证表的内部状态。 */
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(table.elems[(i + 7) % 10], { to_string(i), LinearProbingHashTable::SlotType::FILLED });
    }

    /* 尝试移除一些不存在的元素。如果你的实现有问题，这可能会挂起
     * remove 的实现没有预料到这种情况。
     */
    for (int i = 10; i < 20; i++) {
        EXPECT(!table.remove(to_string(i)));
    }

    /* 验证表的内部状态。 */
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(table.elems[(i + 7) % 10], { to_string(i), LinearProbingHashTable::SlotType::FILLED });
    }

    /* 现在执行实际移除操作。 */
    for (int i = 0; i < 10; i++) {
        EXPECT(table.remove(to_string(i)));
    }
    EXPECT(table.isEmpty());
    EXPECT_EQUAL(table.size(), 0);

    /* 验证表的内部状态。 */
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].type, LinearProbingHashTable::SlotType::TOMBSTONE);
    }
}

PROVIDED_TEST("Stress Test: Handles large numbers of removals (should take at most three seconds).") {
    const int kNumTrials = 50; // 重复多次，以暴露可能潜藏的任何错误。
    for (int trial = 0; trial < kNumTrials; trial++) {
        LinearProbingHashTable table(Hash::random(100));

        const int kNumElems = 75;
        for (int i = 0; i < kNumElems; i++) {
            table.insert(to_string(i));
        }

        EXPECT_EQUAL(table.size(), kNumElems);

        for (int i = 0; i < kNumElems; i++) {
            /* 确认此时仅存在正确的元素。 */
            for (int j = 0; j < kNumElems; j++) {
                EXPECT_EQUAL(table.contains(to_string(j)), bool(j >= i));
            }

            EXPECT(table.remove(to_string(i)));
            EXPECT_EQUAL(table.size(), kNumElems - i - 1);
        }
    }
}

PROVIDED_TEST("Stress Test: Inserts/searches/deletes work in expected time O(1) (should take at most three seconds).") {
    /* 大量槽位。 */
    const int kNumSlots = 1000000;

    /* 使用随机哈希函数创建一个巨大的哈希表。 */
    LinearProbingHashTable table(Hash::random(kNumSlots));

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
PROVIDED_TEST("Stress test: Core functions do not cause stack overflows (should take at most 15 seconds)") {
    SHOW_ERROR("Stress test is disabled by default. To run it, comment out line " + to_string(__LINE__) + " of " + getTail(__FILE__) + ".");
    const int kTableSize = 1000000;

    /* 创建具有 1,000,000 个槽位的表，然后填充前 999,999 个。 */
    Timing::Timer timer;
    timer.start();
    LinearProbingHashTable table(Hash::identity(kTableSize));
    for (int i = 0; i < kTableSize - 1; i++) {
        EXPECT(table.insert(to_string(i)));
    }

    /* 验证表格。 */
    EXPECT_EQUAL(table.size(), kTableSize - 1);
    for (int i = 0; i < kTableSize - 1; i++) {
        EXPECT_EQUAL(table.elems[i], { to_string(i), LinearProbingHashTable::SlotType::FILLED });
    }

    /* 插入值 1,000,000。它想进入槽位 0，但该槽位已占用，因此会
     * 一路移动到表格远端以找到第一个空闲槽位。
     */
    EXPECT(table.insert(to_string(kTableSize)));
    EXPECT_EQUAL(table.size(), kTableSize);
    EXPECT_EQUAL(table.elems[kTableSize - 1], { to_string(kTableSize), LinearProbingHashTable::SlotType::FILLED });

    /* 检查 1000000 是否存在，这需要扫描整个表。 */
    EXPECT(table.contains(to_string(kTableSize)));

    /* 删除 1000000，这需要扫描整个表。 */
    EXPECT(table.remove(to_string(kTableSize)));
    EXPECT_EQUAL(table.elems[kTableSize - 1].type, LinearProbingHashTable::SlotType::TOMBSTONE);
    timer.stop();

    EXPECT_LESS_THAN(timer.elapsed(), 15e9); // 单位为纳秒
}

#include <fstream>
PROVIDED_TEST("Stress Test: Handles large workflows with little free space (should take at most fifteen seconds)") {
    SHOW_ERROR("Stress test is disabled by default. To run it, comment out line " + to_string(__LINE__) + " of " + getTail(__FILE__) + ".");

    Vector<string> english;
    ifstream input("res/EnglishWords.txt");

    for (string word; getline(input, word); ) {
        english += word;
    }

    /* 负载因子 0.97。 */
    Timing::Timer timer;
    timer.start();
    LinearProbingHashTable table(Hash::consistentRandom(english.size() / 0.97));

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
    EXPECT_LESS_THAN(timer.elapsed(), 15e9); // 单位为纳秒
}
