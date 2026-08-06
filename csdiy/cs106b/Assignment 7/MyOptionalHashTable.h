#pragma once

#include "HashFunction.h"
#include "Demos/Utility.h"
#include "GUI/SimpleTest.h"
#include "GUI/MemoryDiagnostics.h"
#include <string>

/* 可供你使用的可选额外哈希表。你不必
 * 实现此哈希表类型；它纯粹是为了在你想要时提供
 * 为基础作业添加扩展内容。
 *
 * 这里没有任何要求；你可以按自己喜欢的方式编写，或者
 * 将其完全留空。
 */
class MyOptionalHashTable {
public:
    /**
     * 使用给定哈希函数构造新的线性探测表
     * 作为参数。（注意，哈希函数允许你决定
     * 使用多少槽位；可调用 hashFn.numSlots() 获取。）
     */
    MyOptionalHashTable(HashFunction<std::string> hashFn);

    /**
     * 释放此哈希表分配的所有内存。
     */
    ~MyOptionalHashTable();

    /**
     * 返回该表是否为空。
     */
    bool isEmpty() const;

    /**
     * 返回表中的元素数量。
     */
    int size() const;

    /**
     * 将指定元素插入此哈希表，并返回是否
     * 它曾经是
     */
    bool insert(const std::string& key);

    /**
     * 返回此哈希表是否包含指定键。
     */
    bool contains(const std::string& key) const;

    /**
     * 从此哈希表中移除指定元素。若该元素不
     * 已存在于哈希表中，则此操作不执行任何动作。随后函数
     * 返回是否删除了任何内容。
     */
    bool remove(const std::string& key);

    /**
     * 输出有助于调试的相关信息。
     */
    void printDebugInfo() const;

private:
    /* 这完全由你决定。 */




    /* 使其与 C++ 正确配合所需的内部处理。 */
    DISALLOW_COPYING_OF(MyOptionalHashTable);
    ALLOW_TEST_ACCESS();
};
