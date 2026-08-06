#include "ChainedHashTable.h"
using namespace std;

ChainedHashTable::ChainedHashTable(HashFunction<string> hashFn) {
    Vector<Vector<string>> buckets(hashFn.numSlots());
    mBuckets    = buckets;

    mHashFn     = hashFn;
    mNumElems   = 0;
}

bool ChainedHashTable::insert(const string& data) {
    /* 如果此元素已存在，则不要添加。 */
    if (contains(data)) {
        return false;
    }

    /* 添加到适当的桶中。 */
    int bucket = mHashFn(data);
    mBuckets[bucket] += data;
    mNumElems++;
    return true;
}

bool ChainedHashTable::contains(const string& elem) const {
    int bucket = mHashFn(elem);
    for (int i = 0; i < mBuckets[bucket].size(); i++) {
        if (elem == mBuckets[bucket][i]) return true;
    }

    return false;
}

bool ChainedHashTable::remove(const string& data) {
    int bucket = mHashFn(data);
    for (int i = 0; i < mBuckets[bucket].size(); i++) {
        if (mBuckets[bucket][i] == data) {
            mBuckets[bucket].remove(i);
            mNumElems--;
            return true;
        }
    }
    return false;
}

int ChainedHashTable::size() const {
    return mNumElems;
}

bool ChainedHashTable::isEmpty() const {
    return size() == 0;
}
