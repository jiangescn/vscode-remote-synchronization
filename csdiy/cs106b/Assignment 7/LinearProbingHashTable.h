#pragma once

#include "HashFunction.h"
#include "Demos/Utility.h"
#include "GUI/SimpleTest.h"
#include "GUI/MemoryDiagnostics.h"
#include <string>

class LinearProbingHashTable {
public:
    /**
     * 使用给定哈希函数构造新的线性探测表
     * 作为参数。（注意，哈希函数允许你决定
     * 使用多少槽位；可调用 hashFn.numSlots() 获取。）
     */
    LinearProbingHashTable(HashFunction<std::string> hashFn);

    /**
     * 释放此哈希表分配的所有内存。
     */
    ~LinearProbingHashTable();

    /**
     * 返回该表是否为空。
     */
    bool isEmpty() const;

    /**
     * 返回表中的元素数量。
     */
    int size() const;

    /**
     * 将指定元素插入此哈希表。若该元素已经
     * 存在时，保持表不变并返回 false，表示
     * 未添加任何内容。
     *
     * 如果表中没有空间插入元素——即每个槽位
     * 已满——应返回 false，表示没有更多空间。
     *
     * 此函数返回元素是否已插入表中。
     */
    bool insert(const std::string& key);

    /**
     * 返回此哈希表是否包含指定键。
     */
    bool contains(const std::string& key) const;

    /**
     * 从此哈希表中移除指定元素。若该元素不
     * 已存在于哈希表中，则此操作为空操作。
     *
     * 你应使用墓碑删除实现此操作——将
     * 将包含该元素的槽位标记为墓碑。
     *
     * 若成功移除元素则返回 true，否则返回 false。
     */
    bool remove(const std::string& key);

    /**
     * 输出有助于调试的相关信息。
     */
    void printDebugInfo() const;

private:
    /* 表示给定槽位状态的类型。请勿修改
     * 此类型，因为测试要求它看起来与当前形式完全一致
     * 当前。
     */
    enum class SlotType {
        EMPTY, FILLED, TOMBSTONE
    };

    /* 表示线性探测表中槽位的类型。请勿
     * 不要修改此类型，因为测试期望其外观与当前完全一致
     * 当前。
     */
    struct Slot {
        std::string value;
        SlotType type;

        TRACK_ALLOCATIONS_OF(Slot);
    };

    /* 指向元素数组的指针。我们的测试要求你的实现使用
     * 元素数组指针必须使用名称“elems”，因此请不要重命名它
     * 变量。
     */
    Slot* elems = nullptr;

    /* TODO：添加所需的私有成员变量、成员函数或成员
     * 所需的类型。可以按任意方式实现此类型，只要
     * 只要自行完成所有内存管理，就可以采用任意方式，
     * 不要使用任何容器类型（例如 Vector、HashSet 等），并且
     * 你使用带墓碑的线性探测。
     *
     * TODO：提交前删除此注释。
     */




    /* 使其与 C++ 正确配合所需的内部处理。 */
    DISALLOW_COPYING_OF(LinearProbingHashTable);
    ALLOW_TEST_ACCESS();
    MAKE_PRINTERS_FOR(SlotType);
    MAKE_PRINTERS_FOR(Slot);
    MAKE_COMPARATORS_FOR(Slot);
};
