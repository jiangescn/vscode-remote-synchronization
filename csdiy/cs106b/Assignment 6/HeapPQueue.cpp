#include "HeapPQueue.h"
using namespace std;

HeapPQueue::HeapPQueue() {
    /* TODO：实现此功能。 */
}

HeapPQueue::~HeapPQueue() {
    /* TODO：实现此功能。 */
}

int HeapPQueue::size() const {
    /* TODO：删除下一行并实现此函数。 */
    return 0;
}

bool HeapPQueue::isEmpty() const {
    /* TODO：删除下一行并实现此函数。 */
    return 0;
}

void HeapPQueue::enqueue(const DataPoint& data) {
    /* TODO：删除下一行并实现此函数。 */
    (void) data;
}

DataPoint HeapPQueue::peek() const {
    /* TODO：删除下一行并实现此函数。 */
    return {};
}

DataPoint HeapPQueue::dequeue() {
    /* TODO：删除下一行并实现此函数。 */
    return {};
}

/* 此函数纯粹供你在测试期间使用。你可以让它执行任何
 * 你喜欢的任何操作，包括什么也不做。评分时不会调用此函数，因此可以放心
 * 可以自由填入对你最有用的任何内容！
 *
 * 如果选择不使用此函数，也不要从这个 .cpp 文件中删除它
 * 文件。只需将函数体留空。
 *
 * TODO：删除此注释，并替换为描述此函数的注释
 * 实际执行的操作。
 */
void HeapPQueue::printDebugInfo() {
    /* TODO：删除此注释，并可选择在此处放置调试代码。 */
}


/* * * * * * 此处以下为测试用例 * * * * * */

/* TODO：在此添加你自己的自定义测试！ */














/* * * * * 此处以下为提供的测试 * * * * */

PROVIDED_TEST("Newly-created heap is empty.") {
    HeapPQueue pq;

    EXPECT(pq.isEmpty());
    EXPECT(pq.size() == 0);
}

PROVIDED_TEST("Newly-created heap allocates an array of the right size.") {
    HeapPQueue pq;

    EXPECT_NOT_EQUAL(pq.elems, nullptr);
    EXPECT_EQUAL(pq.logicalSize, 0);
    EXPECT_EQUAL(pq.allocatedSize, HeapPQueue::INITIAL_SIZE);
}

PROVIDED_TEST("Can enqueue a single element.") {
    HeapPQueue pq;
    pq.enqueue({ "First", 137.0 });

    /* 检查其他字段的有效性。 */
    EXPECT_EQUAL(pq.size(), 1);
    EXPECT_EQUAL(pq.logicalSize, 1);
    EXPECT(!pq.isEmpty());

    /* 优先队列的槽位 0 不使用，因此我们不会检查
     * 其值位于此处。
     *
     * 优先队列的槽位 1 应包含新添加的
     * 元素。
     */
    EXPECT_EQUAL(pq.elems[1], { "First", 137.0 });

    /* 仍有剩余空间，因此无需扩展数组
     * 本应是必要的。
     */
    EXPECT_EQUAL(pq.allocatedSize, HeapPQueue::INITIAL_SIZE);
}

PROVIDED_TEST("Enqueues two elements in sorted order.") {
    HeapPQueue pq;

    /* 按此顺序添加这些项目。 */
    DataPoint one = { "First",  1.6108 };
    DataPoint two = { "Second", 2.7182 };

    pq.enqueue(one);

    /* 确保它存在。 */
    EXPECT_EQUAL(pq.elems[1], one);

    pq.enqueue(two);

    /* 我们应当得到
     *
     * [ 未使用 ] [ 一 ] [ 二 ]
     *
     * 因为 one.weight < two.weight。
     */
    EXPECT_EQUAL(pq.size(), 2);
    EXPECT_EQUAL(pq.elems[1], one);
    EXPECT_EQUAL(pq.elems[2], two);

    /* 仍有剩余空间，因此无需扩展数组
     * 本应是必要的。
     */
    EXPECT_EQUAL(pq.allocatedSize, HeapPQueue::INITIAL_SIZE);
}

PROVIDED_TEST("Enqueues two elements in reverse sorted order.") {
    HeapPQueue pq;

    /* 按此顺序添加这些项目。 */
    DataPoint one = { "First",  3.1415 };
    DataPoint two = { "Second", 2.7182 };

    pq.enqueue(one);

    /* 确保它存在。 */
    EXPECT_EQUAL(pq.elems[1], one);

    pq.enqueue(two);

    /* 我们应当得到
     *
     * [ 未使用 ] [ 二 ] [ 一 ]
     *
     * 因为 one.weight > two.weight。
     */
    EXPECT_EQUAL(pq.size(), 2);
    EXPECT_EQUAL(pq.elems[1], two);
    EXPECT_EQUAL(pq.elems[2], one);

    /* 仍有剩余空间，因此无需扩展数组
     * 本应是必要的。
     */
    EXPECT_EQUAL(pq.allocatedSize, HeapPQueue::INITIAL_SIZE);
}

PROVIDED_TEST("Enqueues three elements in sorted order.") {
    HeapPQueue pq;

    /* 按此顺序添加这些项目。 */
    DataPoint one   = { "First",  1.6108 };
    DataPoint two   = { "Second", 2.7182 };
    DataPoint three = { "Third",  3.1415 };

    pq.enqueue(one);
    pq.enqueue(two);
    pq.enqueue(three);

    /* 应当包含以下内容：
     *
     * [ 未使用 ] [ 一 ] [ 二 ] [ 三 ]
     */
    EXPECT_EQUAL(pq.size(), 3);
    EXPECT_EQUAL(pq.elems[1], one);
    EXPECT_EQUAL(pq.elems[2], two);
    EXPECT_EQUAL(pq.elems[3], three);

    /* 仍有剩余空间，因此无需扩展数组
     * 本应是必要的。
     */
    EXPECT_EQUAL(pq.allocatedSize, HeapPQueue::INITIAL_SIZE);
}

PROVIDED_TEST("Enqueues three elements in reverse-sorted order.") {
    HeapPQueue pq;

    /* 按此顺序添加这些项目。 */
    DataPoint one   = { "First",  161 };
    DataPoint two   = { "Second", 106 };
    DataPoint three = { "Third",  103 };

    pq.enqueue(one);
    pq.enqueue(two);   // 向上冒泡
    pq.enqueue(three); // 向上冒泡

    /* 应当包含以下内容：
     *
     * [ 未使用 ] [ 三 ] [ 一 ] [ 二 ]
     *
     * 原因是插入 2 时应与
     * 一个，而插入 3 时应与 2 交换。
     */
    EXPECT_EQUAL(pq.size(), 3);
    EXPECT_EQUAL(pq.elems[1], three);
    EXPECT_EQUAL(pq.elems[2], one);
    EXPECT_EQUAL(pq.elems[3], two);

    /* 仍有剩余空间，因此无需扩展数组
     * 本应是必要的。
     */
    EXPECT_EQUAL(pq.allocatedSize, HeapPQueue::INITIAL_SIZE);
}

PROVIDED_TEST("Enqueues five elements in sorted order.") {
    HeapPQueue pq;

    /* 按此顺序添加这些项目。 */
    DataPoint one   = { "First",  1 };
    DataPoint two   = { "Second", 2 };
    DataPoint three = { "Third",  3 };
    DataPoint four  = { "Four",   4 };
    DataPoint five  = { "Five",   5 };

    pq.enqueue(one);
    pq.enqueue(two);
    pq.enqueue(three);
    pq.enqueue(four);
    pq.enqueue(five);

    /* 应当包含以下内容：
     *
     * [ 未使用 ] [ 一 ] [ 二 ] [ 三 ] [ 四 ] [ 五 ]
     *
     * 任何插入都不应触发上浮。
     */
    EXPECT_EQUAL(pq.size(), 5);
    EXPECT_EQUAL(pq.elems[1], one);
    EXPECT_EQUAL(pq.elems[2], two);
    EXPECT_EQUAL(pq.elems[3], three);
    EXPECT_EQUAL(pq.elems[4], four);
    EXPECT_EQUAL(pq.elems[5], five);

    /* 我们恰好达到容量。不应发生扩容
     * 发生在这里。
     */
    EXPECT_EQUAL(pq.allocatedSize, HeapPQueue::INITIAL_SIZE);
}

PROVIDED_TEST("Enqueues five elements in reverse-sorted order.") {
    HeapPQueue pq;

    /* 按此顺序添加这些项目。 */
    DataPoint one   = { "First",  10 };
    DataPoint two   = { "Second", 9 };
    DataPoint three = { "Third",  8 };
    DataPoint four  = { "Four",   7 };
    DataPoint five  = { "Five",   6 };

    pq.enqueue(one);
    pq.enqueue(two);
    pq.enqueue(three);
    pq.enqueue(four);
    pq.enqueue(five);

    /* 应当包含以下内容：
     *
     * [ 未使用 ] [ 五 ] [ 四 ] [ 二 ] [ 一 ] [ 三 ]
     *
     * 要理解原因，请拿出纸笔并逐步跟踪
     * 完整经历所执行的确切插入序列。
     */
    EXPECT_EQUAL(pq.size(), 5);
    EXPECT_EQUAL(pq.elems[1], five);
    EXPECT_EQUAL(pq.elems[2], four);
    EXPECT_EQUAL(pq.elems[3], two);
    EXPECT_EQUAL(pq.elems[4], one);
    EXPECT_EQUAL(pq.elems[5], three);

    /* 我们恰好达到容量。不应发生扩容
     * 发生在这里。
     */
    EXPECT_EQUAL(pq.allocatedSize, HeapPQueue::INITIAL_SIZE);
}

PROVIDED_TEST("Enqueue grows the internal array.") {
    HeapPQueue pq;

    /* 按此顺序添加这些项目。 */
    DataPoint one   = { "First",  1 };
    DataPoint two   = { "Second", 2 };
    DataPoint three = { "Third",  3 };
    DataPoint four  = { "Four",   4 };
    DataPoint five  = { "Five",   5 };
    DataPoint six   = { "Six",    6 };

    pq.enqueue(one);
    pq.enqueue(two);
    pq.enqueue(three);
    pq.enqueue(four);
    pq.enqueue(five);

    /* 下面这一项会触发扩容步骤。 */
    auto* oldArray = pq.elems;
    pq.enqueue(six);

    /* 数组应已被新数组替换。 */
    EXPECT_NOT_EQUAL(pq.elems, oldArray);
    EXPECT_EQUAL(pq.allocatedSize, 2 * HeapPQueue::INITIAL_SIZE);

    /* 应当包含以下内容：
     *
     * [ 未使用 ] [ 一 ] [ 二 ] [ 三 ] [ 四 ] [ 五 ] [ 六 ]
     *
     * 任何插入都不应触发上浮。
     */
    EXPECT_EQUAL(pq.elems[1], one);
    EXPECT_EQUAL(pq.elems[2], two);
    EXPECT_EQUAL(pq.elems[3], three);
    EXPECT_EQUAL(pq.elems[4], four);
    EXPECT_EQUAL(pq.elems[5], five);
    EXPECT_EQUAL(pq.elems[6], six);
    EXPECT_EQUAL(pq.size(), 6);
}

PROVIDED_TEST("Enqueue repeatedly grows the internal array.") {
    HeapPQueue pq;

    /* 按排序顺序插入大量值。不应发生上浮
     * 在此过程中发生，但内部数组将
     * 需要多次扩容。
     */
    for (int i = 1; i < 100; i++) {
        pq.enqueue({ to_string(i), double(i) });
        EXPECT_EQUAL(pq.size(), i);

        /* 确认数组内容与预期内容完全匹配
         * 应有的顺序——即元素的排序顺序。
         */
        for (int j = 1; j <= i; j++) {
            EXPECT_EQUAL(pq.elems[j], { to_string(j), double(j) });
        }
    }
}

PROVIDED_TEST("Enqueue can bubble up long chains.") {
    HeapPQueue pq;

    /* 首先创建此堆：
     *
     *                2
     *             /     \
     *          3           4
     *         /  \       /   \
     *        5    6     7     8
     *       / \  / \   / \   /
     *      9 10 11 12 13 14 15
     *
     * 可以按顺序插入所有这些元素来完成
     * 放入优先队列。
     */
    for (int i = 2; i <= 15; i++) {
        pq.enqueue({ to_string(i), double(i) });
    }

    /* 确认队列设置正确。 */
    for (int i = 2; i <= 15; i++) {
        EXPECT_EQUAL(pq.elems[i - 1], { to_string(i), double(i) });
    }
    EXPECT_EQUAL(pq.size(), 14);

    /* 现在，将 1 入队。这会引起一连串交换，
     * 以以下内容结尾：
     *
     *                1
     *             /     \
     *          3           2
     *         /  \       /   \
     *        5    6     7     4
     *       / \  / \   / \   / \
     *      9 10 11 12 13 14 15  8
     */
    pq.enqueue({ "1", 1 });
    EXPECT_EQUAL(pq.size(), 15);

    EXPECT_EQUAL(pq.elems[1],   {  "1",  1 });
    EXPECT_EQUAL(pq.elems[2],   {  "3",  3 });
    EXPECT_EQUAL(pq.elems[3],   {  "2",  2 });
    EXPECT_EQUAL(pq.elems[4],   {  "5",  5 });
    EXPECT_EQUAL(pq.elems[5],   {  "6",  6 });
    EXPECT_EQUAL(pq.elems[6],   {  "7",  7 });
    EXPECT_EQUAL(pq.elems[7],   {  "4",  4 });
    EXPECT_EQUAL(pq.elems[8],   {  "9",  9 });
    EXPECT_EQUAL(pq.elems[9],   { "10", 10 });
    EXPECT_EQUAL(pq.elems[10],  { "11", 11 });
    EXPECT_EQUAL(pq.elems[11],  { "12", 12 });
    EXPECT_EQUAL(pq.elems[12],  { "13", 13 });
    EXPECT_EQUAL(pq.elems[13],  { "14", 14 });
    EXPECT_EQUAL(pq.elems[14],  { "15", 15 });
    EXPECT_EQUAL(pq.elems[15],  {  "8",  8 });
}

PROVIDED_TEST("Can enqueue and dequeue a single element.") {
    HeapPQueue pq;

    DataPoint first = { "First", 137 };
    pq.enqueue(first);

    EXPECT_EQUAL(pq.dequeue(), first);
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT(pq.isEmpty());
}

PROVIDED_TEST("Reports an error when dequeuing from an empty queue.") {
    HeapPQueue pq;

    EXPECT_ERROR(pq.dequeue());
}

PROVIDED_TEST("Can bubble down to the left.") {
    HeapPQueue pq;

    /* 构造如下堆：
     *
     *         1
     *        / \
     *       2   3
     *      /
     *     4
     */
    DataPoint v1 = { "First",  1 };
    DataPoint v2 = { "Second", 2 };
    DataPoint v3 = { "Third",  3 };
    DataPoint v4 = { "Fourth", 4 };

    pq.enqueue(v1);
    pq.enqueue(v2);
    pq.enqueue(v3);
    pq.enqueue(v4);

    EXPECT_EQUAL(pq.size(), 4);
    EXPECT_EQUAL(pq.elems[1], v1);
    EXPECT_EQUAL(pq.elems[2], v2);
    EXPECT_EQUAL(pq.elems[3], v3);
    EXPECT_EQUAL(pq.elems[4], v4);

    /* 执行一次出队，随后第一步变为：
     *
     *         4
     *        / \
     *       2   3
     *
     * 然后这应将 4 向左下交换，得到
     *
     *         2
     *        / \
     *       4   3
     */
     EXPECT_EQUAL(pq.dequeue(), v1);
     EXPECT_EQUAL(pq.size(), 3);
     EXPECT_EQUAL(pq.elems[1], v2);
     EXPECT_EQUAL(pq.elems[2], v4);
     EXPECT_EQUAL(pq.elems[3], v3);
}

PROVIDED_TEST("Can bubble down to the right.") {
    HeapPQueue pq;

    /* 构造如下堆：
     *
     *         1
     *        / \
     *       3   2
     *      /
     *     4
     */
    DataPoint v1 = { "First",  1 };
    DataPoint v2 = { "Second", 2 };
    DataPoint v3 = { "Third",  3 };
    DataPoint v4 = { "Fourth", 4 };

    pq.enqueue(v1);
    pq.enqueue(v3);
    pq.enqueue(v2);
    pq.enqueue(v4);

    EXPECT_EQUAL(pq.size(), 4);
    EXPECT_EQUAL(pq.elems[1], v1);
    EXPECT_EQUAL(pq.elems[2], v3);
    EXPECT_EQUAL(pq.elems[3], v2);
    EXPECT_EQUAL(pq.elems[4], v4);

    /* 执行一次出队，随后第一步变为：
     *
     *         4
     *        / \
     *       3   2
     *
     * 然后这应将 4 向右下交换，得到
     *
     *         2
     *        / \
     *       3   4
     */
     EXPECT_EQUAL(pq.dequeue(), v1);
     EXPECT_EQUAL(pq.size(), 3);
     EXPECT_EQUAL(pq.elems[1], v2);
     EXPECT_EQUAL(pq.elems[2], v3);
     EXPECT_EQUAL(pq.elems[3], v4);
}

PROVIDED_TEST("Can bubble down two layers.") {
    HeapPQueue pq;

    /* 构造如下堆：
     *
     *           1
     *        /     \
     *       2       3
     *      / \     /
     *     4   5   6
     */
    DataPoint v1 = { "First",  1 };
    DataPoint v2 = { "Second", 2 };
    DataPoint v3 = { "Third",  3 };
    DataPoint v4 = { "Fourth", 4 };
    DataPoint v5 = { "Fifth",  5 };
    DataPoint v6 = { "Sixth",  6 };

    pq.enqueue(v1);
    pq.enqueue(v2);
    pq.enqueue(v3);
    pq.enqueue(v4);
    pq.enqueue(v5);
    pq.enqueue(v6);

    EXPECT_EQUAL(pq.size(), 6);
    EXPECT_EQUAL(pq.elems[1], v1);
    EXPECT_EQUAL(pq.elems[2], v2);
    EXPECT_EQUAL(pq.elems[3], v3);
    EXPECT_EQUAL(pq.elems[4], v4);
    EXPECT_EQUAL(pq.elems[5], v5);
    EXPECT_EQUAL(pq.elems[6], v6);

    /* 执行一次出队，随后第一步变为：
     *
     *           6
     *        /     \
     *       2       3
     *      / \
     *     4   5
     *
     * 然后这应将 6 向左下交换，得到
     *
     *           2
     *        /     \
     *       6       3
     *      / \
     *     4   5
     *
     * 这应再次将 6 向左下交换，得到
     *
     *           2
     *        /     \
     *       4       3
     *      / \
     *     6   5
     */
     EXPECT_EQUAL(pq.dequeue(), v1);
     EXPECT_EQUAL(pq.size(), 5);
     EXPECT_EQUAL(pq.elems[1], v2);
     EXPECT_EQUAL(pq.elems[2], v4);
     EXPECT_EQUAL(pq.elems[3], v3);
     EXPECT_EQUAL(pq.elems[4], v6);
     EXPECT_EQUAL(pq.elems[5], v5);
}

PROVIDED_TEST("Can bubble down when only one child exists.") {
    HeapPQueue pq;

    /* 构造如下堆：
     *
     *         1
     *        / \
     *       2   3
     *      / \
     *     4   5
     */
    DataPoint v1 = { "First",  1 };
    DataPoint v2 = { "Second", 2 };
    DataPoint v3 = { "Third",  3 };
    DataPoint v4 = { "Fourth", 4 };
    DataPoint v5 = { "Fifth",  5 };

    pq.enqueue(v1);
    pq.enqueue(v2);
    pq.enqueue(v3);
    pq.enqueue(v4);
    pq.enqueue(v5);

    EXPECT_EQUAL(pq.size(), 5);
    EXPECT_EQUAL(pq.elems[1], v1);
    EXPECT_EQUAL(pq.elems[2], v2);
    EXPECT_EQUAL(pq.elems[3], v3);
    EXPECT_EQUAL(pq.elems[4], v4);
    EXPECT_EQUAL(pq.elems[5], v5);

    /* 执行一次出队，随后第一步变为：
     *
     *         5
     *        / \
     *       2   3
     *      /
     *     4
     *
     * 然后这应将 5 向左下交换，得到
     *
     *         2
     *        / \
     *       5   3
     *      /
     *     4
     *
     * 这应再次将 5 向左下交换，得到
     *
     *         2
     *        / \
     *       4   3
     *      /
     *     5
     */
     EXPECT_EQUAL(pq.dequeue(), v1);
     EXPECT_EQUAL(pq.size(), 4);
     EXPECT_EQUAL(pq.elems[1], v2);
     EXPECT_EQUAL(pq.elems[2], v4);
     EXPECT_EQUAL(pq.elems[3], v3);
     EXPECT_EQUAL(pq.elems[4], v5);
}

PROVIDED_TEST("Enqueue / dequeue single element") {
    HeapPQueue pq;
    DataPoint point = { "enqueue me!", 4 };
    pq.enqueue(point);
    EXPECT_EQUAL(pq.size(), 1);
    EXPECT_EQUAL(pq.isEmpty(), false);

    EXPECT_EQUAL(pq.dequeue(), point);
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);

    pq.enqueue(point);
    EXPECT_EQUAL(pq.size(), 1);
    EXPECT_EQUAL(pq.isEmpty(), false);

    EXPECT_EQUAL(pq.dequeue(), point);
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}

PROVIDED_TEST("Dequeue / peek on empty heap throws error") {
    HeapPQueue pq;

    EXPECT(pq.isEmpty());
    EXPECT_ERROR(pq.dequeue());
    EXPECT_ERROR(pq.peek());
}

PROVIDED_TEST("Enqueue elements in sorted order.") {
    HeapPQueue pq;
    for (int i = 0; i < 10; i++) {
        pq.enqueue({ "elem" + to_string(i), double(i) });
    }

    EXPECT_EQUAL(pq.size(), 10);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(pq.peek(), { "elem" + to_string(i), double(i) });
        EXPECT_EQUAL(pq.dequeue(), { "elem" + to_string(i), double(i) });
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}

PROVIDED_TEST("Enqueue many elements in sorted order.") {
    HeapPQueue pq;
    for (int i = 0; i < 10000; i++) {
        pq.enqueue({ "elem" + to_string(i), double(i) });
    }

    EXPECT_EQUAL(pq.size(), 10000);
    for (int i = 0; i < 10000; i++) {
        EXPECT_EQUAL(pq.peek(), { "elem" + to_string(i), double(i) });
        EXPECT_EQUAL(pq.dequeue(), { "elem" + to_string(i), double(i) });
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}

PROVIDED_TEST("Enqueue elements in reverse-sorted order.") {
    HeapPQueue pq;
    for (int i = 10; i >= 0; i--) {
        pq.enqueue({ "elem" + to_string(i), double(i) });
    }

    EXPECT_EQUAL(pq.size(), 11);
    for (int i = 0; i <= 10; i++) {
        EXPECT_EQUAL(pq.peek(), { "elem" + to_string(i), double(i) });
        EXPECT_EQUAL(pq.dequeue(), { "elem" + to_string(i), double(i) });
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}

PROVIDED_TEST("Enqueue many elements in reverse-sorted order.") {
    HeapPQueue pq;
    for (int i = 10000; i >= 0; i--) {
        pq.enqueue({ "elem" + to_string(i), double(i) });
    }

    EXPECT_EQUAL(pq.size(), 10001);
    for (int i = 0; i <= 10000; i++) {
        auto removed = pq.dequeue();
        DataPoint expected = {
            "elem" + to_string(i), double(i)
        };
        EXPECT_EQUAL(removed, expected);
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}

PROVIDED_TEST("Insert ascending and descending sequences.") {
    HeapPQueue pq;
    for (int i = 0; i < 20; i++) {
        pq.enqueue({ "a" + to_string(i), 2 * double(i) });
    }
    for (int i = 19; i >= 0; i--) {
        pq.enqueue({ "b" + to_string(i), 2 * double(i) + 1 });
    }

    EXPECT_EQUAL(pq.size(), 40);
    for (int i = 0; i < 40; i++) {
        auto removed = pq.dequeue();
        EXPECT_EQUAL(removed.weight, i);
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}

PROVIDED_TEST("Insert large ascending and descending sequences.") {
    HeapPQueue pq;
    for (int i = 0; i < 20000; i++) {
        pq.enqueue({ "a" + to_string(i), 2 * double(i) });
    }
    for (int i = 19999; i >= 0; i--) {
        pq.enqueue({ "b" + to_string(i), 2 * double(i) + 1 });
    }

    EXPECT_EQUAL(pq.size(), 40000);
    for (int i = 0; i < 40000; i++) {
        auto removed = pq.dequeue();
        EXPECT_EQUAL(removed.weight, i);
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}

PROVIDED_TEST("Insert random permutation.") {
    Vector<DataPoint> sequence = {
        { "A", 0 },
        { "D", 3 },
        { "F", 5 },
        { "G", 6 },
        { "C", 2 },
        { "H", 7 },
        { "I", 8 },
        { "B", 1 },
        { "E", 4 },
        { "J", 9 },
    };

    HeapPQueue pq;
    for (DataPoint elem: sequence) {
        pq.enqueue(elem);
    }

    EXPECT_EQUAL(pq.size(), sequence.size());

    for (int i = 0; i < 10; i++) {
        auto removed = pq.dequeue();
        DataPoint expected = {
            string(1, 'A' + i), double(i)
        };
        EXPECT_EQUAL(removed, expected);
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}

PROVIDED_TEST("Insert duplicate elements.") {
    HeapPQueue pq;
    for (int i = 0; i < 20; i++) {
        pq.enqueue({ "a" + to_string(i), double(i) });
    }
    for (int i = 19; i >= 0; i--) {
        pq.enqueue({ "b" + to_string(i), double(i) });
    }

    EXPECT_EQUAL(pq.size(), 40);
    for (int i = 0; i < 20; i++) {
        auto one = pq.dequeue();
        auto two = pq.dequeue();

        EXPECT_EQUAL(one.weight, i);
        EXPECT_EQUAL(two.weight, i);
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}

PROVIDED_TEST("Insert many duplicate elements.") {
    HeapPQueue pq;
    for (int i = 0; i < 20000; i++) {
        pq.enqueue({ "a" + to_string(i), double(i) });
    }
    for (int i = 19999; i >= 0; i--) {
        pq.enqueue({ "b" + to_string(i), double(i) });
    }

    EXPECT_EQUAL(pq.size(), 40000);
    for (int i = 0; i < 20000; i++) {
        auto one = pq.dequeue();
        auto two = pq.dequeue();

        EXPECT_EQUAL(one.weight, i);
        EXPECT_EQUAL(two.weight, i);
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}

PROVIDED_TEST("Handles data points with empty string name.") {
    HeapPQueue pq;
    for (int i = 0; i < 10; i++) {
        pq.enqueue({ "" , double(i) });
    }
    EXPECT_EQUAL(pq.size(), 10);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(pq.dequeue(), { "", double(i) });
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT(pq.isEmpty());
}

PROVIDED_TEST("Handles many data points with empty string name.") {
    HeapPQueue pq;
    for (int i = 0; i < 10000; i++) {
        pq.enqueue({ "" , double(i) });
    }
    EXPECT_EQUAL(pq.size(), 10000);
    for (int i = 0; i < 10000; i++) {
        EXPECT_EQUAL(pq.dequeue(), { "", double(i) });
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT(pq.isEmpty());
}

PROVIDED_TEST("Handles data points with negative weights.") {
    HeapPQueue pq;
    for (int i = -10; i < 10; i++) {
        pq.enqueue({ "" , double(i) });
    }
    EXPECT_EQUAL(pq.size(), 20);
    for (int i = -10; i < 10; i++) {
        EXPECT_EQUAL(pq.dequeue().weight, i);
    }
}

PROVIDED_TEST("Handles many data points with negative weights.") {
    HeapPQueue pq;
    for (int i = -10000; i < 10000; i++) {
        pq.enqueue({ "" , double(i) });
    }
    EXPECT_EQUAL(pq.size(), 20000);
    for (int i = -10000; i < 10000; i++) {
        EXPECT_EQUAL(pq.dequeue().weight, i);
    }
}

PROVIDED_TEST("Interleave enqueues and dequeues.") {
    HeapPQueue pq;
    int n = 100;
    for (int i = n / 2; i < n; i++) {
        pq.enqueue({"", double(i)});
    }
    EXPECT_EQUAL(pq.size(), n / 2);
    for (int i = n / 2; i < n; i++) {
        EXPECT_EQUAL(pq.dequeue().weight, i);
    }
    EXPECT_EQUAL(pq.size(), 0);

    for (int i = 0; i < n / 2; i++) {
        pq.enqueue({"", double(i)});
    }
    EXPECT_EQUAL(pq.size(), n / 2);
    for (int i = 0; i < n / 2; i++) {
        EXPECT_EQUAL(pq.dequeue().weight, i);
    }
    EXPECT_EQUAL(pq.size(), 0);
}

PROVIDED_TEST("Interleave many enqueues and dequeues.") {
    HeapPQueue pq;
    int n = 10000;
    for (int i = n / 2; i < n; i++) {
        pq.enqueue({"", double(i)});
    }
    EXPECT_EQUAL(pq.size(), n / 2);
    for (int i = n / 2; i < n; i++) {
        EXPECT_EQUAL(pq.dequeue().weight, i);
    }
    EXPECT_EQUAL(pq.size(), 0);

    for (int i = 0; i < n / 2; i++) {
        pq.enqueue({"", double(i)});
    }
    EXPECT_EQUAL(pq.size(), n / 2);
    for (int i = 0; i < n / 2; i++) {
        EXPECT_EQUAL(pq.dequeue().weight, i);
    }
    EXPECT_EQUAL(pq.size(), 0);
}

PROVIDED_TEST("Stress test: cycle 250,000 elems (should take at most a few seconds)") {
    HeapPQueue pq;
    int n = 250000;
    for (int i = 0; i < n; i++) {
        pq.enqueue({ "", randomReal(0, 100000) });
    }
    EXPECT_EQUAL(pq.size(), n);

    for (int i = 0; i < n; i++) {
        pq.dequeue();
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);

    for (int i = 0; i < n; i++) {
        pq.enqueue({ "", randomReal(0, 100000) });
    }
    EXPECT_EQUAL(pq.size(), n);
}
