#ifndef ChainedHashTable_Included
#define ChainedHashTable_Included

#include "Demos/Utility.h"
#include "HashFunction.h"
#include "vector.h"

class ChainedHashTable {
public:
    /**
     * 构造使用给定哈希函数的新链式哈希表
     * 作为参数。
     */
    ChainedHashTable(HashFunction<std::string> hashFn);

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
     * 存在时，保持表不变。
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
     * 若成功移除元素则返回 true，否则返回 false。
     */
    bool remove(const std::string& key);


private:
    Vector<Vector<std::string>> mBuckets;
    int                         mNumElems;
    HashFunction<std::string>   mHashFn;

    DISALLOW_COPYING_OF(ChainedHashTable);
};

#endif
