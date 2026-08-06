#pragma once

#include "HashFunction.h"
#include "Demos/Utility.h"
#include "GUI/SimpleTest.h"
#include "GUI/MemoryDiagnostics.h"
#include <string>

class RobinHoodHashTable {
public:
    /**
     * 构造使用给定哈希函数的新 Robin Hood 哈希表
     * 作为参数。（注意，哈希函数允许你决定
     * 使用多少槽位；可调用 hashFn.numSlots() 获取。）
     */
    RobinHoodHashTable(HashFunction<std::string> hashFn);

    /**
     * 释放此哈希表分配的所有内存。
     */
    ~RobinHoodHashTable();

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
     * 存在时，保持表不变。如果表中没有空间
     * 无法插入元素——即每个槽位都已满——此时应返回
     * 返回 false，表示没有更多空间。
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
     * 你应按要求使用后移删除实现此操作，
     * 课堂中讲述的方式。
     *
     * 若成功移除元素则返回 true，否则返回 false。
     */
    bool remove(const std::string& key);

    /**
     * 输出有助于调试的相关信息。
     */
    void printDebugInfo() const;

private:
    /* 表示表中槽位的类型。已占用槽位存储其距离
     * 设为距初始槽位的距离（从该位置开始测量
     * 从槽位开始向前遍历，必要时绕回表头）。空的
     * 槽位的距离设置为常量 EMPTY_SLOT。
     *
     * 测试期望 Slot 类型与此完全一致；请不要
     * 修改此类型。
     */
    struct Slot {
        std::string value;
        int distance;

        TRACK_ALLOCATIONS_OF(Slot);
    };

    /* 用于表示空槽位的常量。距离不能为负，
     * 这样它不会被误认为有效距离。
     */
    static const int EMPTY_SLOT = -137;

    /* 指向元素的指针。测试期望此字段存在，因此请不要
     * 不要更改此定义。
     */
    Slot* elems = nullptr;

    /* TODO：添加所需的私有成员变量、成员函数或成员
     * 所需的类型。可以按任意方式实现此类型，只要
     * 只要自行完成所有内存管理，就可以采用任意方式，
     * 不要使用任何容器类型（例如 Vector、HashSet 等），并且
     * 你使用带后移删除的 Robin Hood 哈希。
     *
     * TODO：提交前删除此注释。
     */




    /* 使其与 C++ 正确配合所需的内部处理。 */
    DISALLOW_COPYING_OF(RobinHoodHashTable);
    ALLOW_TEST_ACCESS();
    MAKE_PRINTERS_FOR(Slot);
    MAKE_COMPARATORS_FOR(Slot);
};
