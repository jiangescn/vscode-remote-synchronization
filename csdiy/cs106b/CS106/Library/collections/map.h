/*
 * 文件：map.h
 * -----------
 * 此文件导出模板类 <code>Map</code>，该类
 * 维护一个<i>键</i>-<i>值</i>对集合。
 */

#ifndef _map_h
#define _map_h

#include <cstdlib>
#include <initializer_list>
#include <utility>
#include <type_traits>
#include <map>
#include <functional>

#include "collections.h"
#include "error.h"
#include "hashcode.h"
#include "stack.h"
#include "vector.h"

/*
 * 类：Map<KeyType,ValueType>
 * -----------------------------
 * 此类维护 <b><i>键</i></b>与
 * <b><i>值</i></b>。用于键和值的类型
 * 使用模板指定，这使得可以使用
 * 将此结构与任何数据类型一起使用。
 */
template <typename KeyType, typename ValueType>
class Map {
public:
    /*
     * 构造函数：Map
     * 用法：Map<KeyType,ValueType> map;
     * ----------------------------------
     * 初始化一个新的空映射，用于关联以下类型的键和值：
     * 指定类型。
     */
    Map();

    /*
     * 构造函数：Map
     * 用法：Map<KeyType,ValueType> map(lessFunc);
     * --------------------------------------------
     * 初始化一个新的空映射，用于关联以下类型的键和值：
     * 指定类型，并使用给定的“小于”比较函数
     * 用于对之后添加的任何键进行排序。
     * 该函数可以按值或以下方式接受要比较的两个键
     * 或通过 const 引用。
     */
    Map(std::function<bool (const KeyType&, const KeyType&)> lessFunc);

    /*
     * 构造函数：Map
     * 用法：Map<ValueType> map {{"a", 1}, {"b", 2}, {"c", 3}};
     * ---------------------------------------------------------
     * 初始化存储给定键值对的新映射。
     * 请注意，键值对在内部按键排序存储，而不是
     * 不一定与它们在初始化列表中的书写顺序相同。
     */
    Map(std::initializer_list<std::pair<const KeyType, ValueType>> list);

    /*
     * 构造函数：Map
     * 用法：Map<ValueType> map({{"a", 1}, {"b", 2}, {"c", 3}}, lessFunc);
     * --------------------------------------------------------------------
     * 初始化一个新的空映射，用于关联以下类型的键和值：
     * 指定类型，并使用给定的“小于”比较函数
     * 用于对之后添加的任何键进行排序。
     * 该函数可以按值或以下方式接受要比较的两个键
     * 或通过 const 引用。
     */
    Map(std::initializer_list<std::pair<const KeyType, ValueType>> list,
        std::function<bool (const KeyType&, const KeyType&)> lessFunc);

    /*
     * 析构函数：~Map
     * ----------------
     * 释放与此映射关联的所有堆存储。
     */
    virtual ~Map() = default;

    /*
     * 方法：clear
     * 用法：map.clear();
     * -------------------
     * 移除此映射中的所有条目。
     */
    void clear();

    /*
     * 方法：containsKey
     * 用法：if (map.containsKey(key)) ...
     * ------------------------------------
     * 如果存在 <code>key</code> 的条目，则返回 <code>true</code>
     * 在此映射中。
     */
    bool containsKey(const KeyType& key) const;

    /*
     * 方法：equals
     * 用法：if (map.equals(map2)) ...
     * --------------------------------
     * 如果两个映射包含完全相同的内容，则返回 <code>true</code>
     * 键值对时为 true，否则为 false。
     */
    bool equals(const Map& map2) const;

    /*
     * 方法：firstKey
     * 用法：KeyType value = map.firstKey();
     * --------------------------------------
     * 按照以下方式建立的顺序返回映射中的第一个键：
     * <code>for-each</code> 循环。若映射为空，则产生错误。
     */
    KeyType firstKey() const;

    /*
     * 方法：get
     * 用法：ValueType value = map.get(key);
     * --------------------------------------
     * 返回此映射中与 <code>key</code> 关联的值。
     * 若找不到 <code>key</code>，<code>get</code> 返回
     * <code>ValueType</code> 的默认值。
     */
    ValueType get(const KeyType& key) const;

    /*
     * 方法：isEmpty
     * 用法：if (map.isEmpty()) ...
     * -----------------------------
     * 如果此映射不包含任何条目，则返回 <code>true</code>。
     */
    bool isEmpty() const;

    /*
     * 方法：keys
     * 用法：Vector<KeyType> keys = map.keys();
     * -----------------------------------------
     * 返回包含此映射中所有键的集合。
     * 请注意，此实现会对键进行深拷贝，
     * 因此在大型映射上调用效率较低。
     */
    Vector<KeyType> keys() const;

    /*
     * 方法：lastKey
     * 用法：KeyType value = map.lastKey();
     * ------------------------------------
     * 按照以下方式建立的顺序返回映射中的最后一个键：
     * <code>for-each</code> 循环。若映射为空，则产生错误。
     */
    KeyType lastKey() const;

    /*
     * 方法：mapAll
     * 用法：map.mapAll(fn);
     * ----------------------
     * 遍历映射条目，并调用 <code>fn(key, value)</code>
     * 分别处理每一个。键按以下定义的升序处理
     * 由比较函数决定。
     */
    void mapAll(std::function<void (const KeyType&, const ValueType&)> fn) const;

    /*
     * 方法：put
     * 用法：map.put(key, value);
     * ---------------------------
     * 在此映射中将 <code>key</code> 与 <code>value</code> 关联。
     * 与 <code>key</code> 关联的任何旧值都会被替换
     * 被新值替换。
     */
    void put(const KeyType& key, const ValueType& value);

    /*
     * 方法：putAll
     * 用法：map.putAll(map2);
     * ------------------------
     * 将给定映射中的所有键值对添加到此映射。
     * 若两个映射包含相同键的键值对，则采用 map2 中的
     * 替换此映射中的对应项。
     * 还可以传入由键值对组成的初始化列表，例如 {{"a", 1}, {"b", 2}, {"c", 3}}。
     * 返回对此映射的引用。
     */
    Map& putAll(const Map& map2);

    /*
     * 方法：remove
     * 用法：map.remove(key);
     * -----------------------
     * 从此映射中移除 <code>key</code> 的任何条目。
     */
    void remove(const KeyType& key);

    /*
     * 方法：removeAll
     * 用法：map.removeAll(map2);
     * ---------------------------
     * 从此映射中移除包含在给定映射中的所有键/值对。
     * 若两个映射都包含同一个键，但该键对应不同值，则
     * 该映射不会被移除。
     * 还可以传入由键值对组成的初始化列表，例如 {{"a", 1}, {"b", 2}, {"c", 3}}。
     * 返回对此映射的引用。
     */
    Map& removeAll(const Map& map2);

    /*
     * 方法：retainAll
     * 用法：map.retainAll(map2);
     * ---------------------------
     * 从此映射中移除不包含在给定映射中的所有键/值对。
     * 若两个映射都包含同一个键，但该键对应不同值，则
     * 该映射将被移除。
     * 还可以传入由键值对组成的初始化列表，例如 {{"a", 1}, {"b", 2}, {"c", 3}}。
     * 返回对此映射的引用。
     */
    Map& retainAll(const Map& map2);

    /*
     * 方法：size
     * 用法：int nEntries = map.size();
     * ---------------------------------
     * 返回此映射中的条目数。
     */
    int size() const;

    /*
     * 方法：toString
     * 用法：string str = map.toString();
     * -----------------------------------
     * 将映射转换为可打印的字符串表示。
     */
    std::string toString() const;

    /*
     * 方法：values
     * 用法：Vector<ValueType> values = map.values();
     * -----------------------------------------------
     * 返回包含此映射中所有值的集合。
     * 请注意，此实现会对值进行深拷贝，
     * 因此在大型映射上调用效率较低。
     */
    Vector<ValueType> values() const;

    /*
     * 运算符：[]
     * 用法：map[key]
     * ---------------
     * 选择与 <code>key</code> 关联的值。此语法
     * 使我们很容易把映射理解为“关联数组”
     * 按键类型索引。若 <code>key</code> 已存在
     * 若键存在于映射中，此函数返回对其关联
     * 值。如果键不在映射中，则创建一个新条目
     * 其值被设置为该值类型的默认值。
     */
    ValueType& operator [](const KeyType& key);
    ValueType operator [](const KeyType& key) const;

    /*
     * 运算符：==
     * 用法：if (map1 == map2) ...
     * ----------------------------
     * 比较两个映射是否相等。
     */
    bool operator ==(const Map& map2) const;

    /*
     * 运算符：!=
     * 用法：if (map1 != map2) ...
     * ----------------------------
     * 比较两个映射是否不相等。
     */
    bool operator !=(const Map& map2) const;

    /*
     * 运算符：<、<=、>、>=
     * 用法：if (map1 < map2) ...
     * ---------------------------
     * 用于比较两个映射的关系运算符。
     * <、>、<=、>= 运算符要求 ValueType 定义 < 运算符
     * 以便逐对比较各元素。
     */
    bool operator <(const Map& map2) const;
    bool operator <=(const Map& map2) const;
    bool operator >(const Map& map2) const;
    bool operator >=(const Map& map2) const;

    /*
     * 运算符：+
     * 用法：map1 + map2
     * ------------------
     * 返回两个映射的并集，等价于第一个映射的副本
     * 等价于在第一个映射上调用 putAll，并将第二个映射作为参数传入。
     * 若两个映射都包含同一键的映射关系，则
     * 优先采用第二个映射中的值。
     * 还可以传入由键值对组成的初始化列表，例如 {{"a", 1}, {"b", 2}, {"c", 3}}。
     */
    Map operator +(const Map& map2) const;

    /*
     * 运算符：+=
     * 用法：map1 += map2;
     * --------------------
     * 将给定映射中的所有键值对添加到此映射。
     * 等价于调用 putAll(map2)。
     * 还可以传入由键值对组成的初始化列表，例如 {{"a", 1}, {"b", 2}, {"c", 3}}。
     */
    Map& operator +=(const Map& map2);

    /*
     * 运算符：-
     * 用法：map1 - map2
     * ------------------
     * 返回两个映射的差集，等价于第一个映射的副本
     * 等价于在第一个映射上调用 removeAll，并将第二个映射作为参数传入。
     * 还可以传入由键值对组成的初始化列表，例如 {{"a", 1}, {"b", 2}, {"c", 3}}。
     */
    Map operator -(const Map& map2) const;

    /*
     * 运算符：-=
     * 用法：map1 -= map2;
     * --------------------
     * 从此映射中移除给定映射中的所有键/值对。
     * 等价于调用 removeAll(map2)。
     * 还可以传入由键值对组成的初始化列表，例如 {{"a", 1}, {"b", 2}, {"c", 3}}。
     */
    Map& operator -=(const Map& map2);

    /*
     * 运算符：*
     * 用法：map1 * map2
     * ------------------
     * 返回两个映射的交集，等价于第一个映射的副本
     * 等价于在第一个映射上调用 retainAll，并将第二个映射作为参数传入。
     * 还可以传入由键值对组成的初始化列表，例如 {{"a", 1}, {"b", 2}, {"c", 3}}。
     */
    Map operator *(const Map& map2) const;

    /*
     * 运算符：*=
     * 用法：map1 *= map2;
     * ---------------------
     * 从此映射中移除给定映射中找不到的所有键/值对。
     * 等价于调用 retainAll(map2)。
     * 还可以传入由键值对组成的初始化列表，例如 {{"a", 1}, {"b", 2}, {"c", 3}}。
     */
    Map& operator *=(const Map& map2);

    /*
     * 其他 Map 操作
     * -------------------------
     * 除本接口中列出的方法外，Map
     * 类支持以下操作：
     *
     *   - 使用 << 和 >> 运算符进行流输入/输出
     *   - 为复制构造函数和赋值运算符实现深拷贝
     *   - 使用基于范围的 for 语句和 STL 迭代器进行迭代
     *
     * 所有迭代保证按以下方式建立的顺序进行：
     * 传给构造函数的比较函数，通常
     * 与键类型的顺序一致。
     */

    /* 私有部分 */

    /**********************************************************************/
    /* 注意：文件中此处以下的所有内容在逻辑上都属于    */
    /* 属于实现细节，客户端无需关注。    */
    /**********************************************************************/

private:
    using MapType = std::map<KeyType, ValueType, std::function<bool(const KeyType&, const KeyType&)>>;
    MapType _elements;
    stanfordcpplib::collections::VersionTracker _version;

public:
    /*
     * 隐藏功能
     * ---------------
     * 此文件的剩余部分包含实现以下功能所需的代码：
     * 支持深复制和迭代。将这些方法包含在
     * 接口的公共部分会使该接口更加
     * 普通客户端难以理解。
     */

    using const_iterator = stanfordcpplib::collections::ProjectingIterator<stanfordcpplib::collections::CheckedIterator<typename MapType::const_iterator>>;
    using iterator = const_iterator;

    const_iterator begin() const;
    const_iterator end() const;
};

template <typename KeyType, typename ValueType>
Map<KeyType, ValueType>::Map() : _elements(stanfordcpplib::collections::checkedLess<KeyType>()) {
    // 已在初始化器中处理
}

template <typename KeyType, typename ValueType>
Map<KeyType, ValueType>::Map(std::function<bool(const KeyType&, const KeyType&)> lessFunc)
        : _elements(lessFunc) {
}

template <typename KeyType, typename ValueType>
Map<KeyType, ValueType>::Map(std::initializer_list<std::pair<const KeyType, ValueType>> list)
        : _elements(list, stanfordcpplib::collections::checkedLess<KeyType>()) {
    // 已在初始化器中处理
}

template <typename KeyType, typename ValueType>
Map<KeyType, ValueType>::Map(std::initializer_list<std::pair<const KeyType, ValueType>> list,
                             std::function<bool(const KeyType&, const KeyType&)> lessFunc)
        : _elements(list, lessFunc) {
}

template <typename KeyType, typename ValueType>
KeyType Map<KeyType, ValueType>::lastKey() const {
    if (isEmpty()) {
        error("Map::lastKey: map is empty");
    }
    return _elements.rbegin()->first;
}

template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::clear() {
    _elements.clear();
    _version.update();
}

template <typename KeyType, typename ValueType>
bool Map<KeyType, ValueType>::containsKey(const KeyType& key) const {
    return !!_elements.count(key);
}

template <typename KeyType, typename ValueType>
bool Map<KeyType, ValueType>::equals(const Map<KeyType, ValueType>& map2) const {
    return stanfordcpplib::collections::equalsMap(*this, map2);
}

template <typename KeyType, typename ValueType>
KeyType Map<KeyType, ValueType>::firstKey() const {
    if (isEmpty()) {
        error("Map::firstKey: map is empty");
    }
    return _elements.begin()->first;
}

template <typename KeyType, typename ValueType>
ValueType Map<KeyType, ValueType>::get(const KeyType& key) const {
    auto itr = _elements.find(key);
    return itr == _elements.end()? ValueType() : itr->second;
}

template <typename KeyType, typename ValueType>
bool Map<KeyType, ValueType>::isEmpty() const {
    return _elements.empty();
}

template <typename KeyType,typename ValueType>
Vector<KeyType> Map<KeyType, ValueType>::keys() const {
    Vector<KeyType> keyset;
    for (const auto& entry: _elements) {
        keyset.add(entry.first);
    }
    return keyset;
}

template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::mapAll(std::function<void (const KeyType&, const ValueType&)> fn) const {
    for (const auto& entry: _elements) {
        fn(entry.first, entry.second);
    }
}

template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::put(const KeyType& key,
                                  const ValueType& value) {
    int presize = size();
    _elements[key] = value;
    if (presize != size()) _version.update();
}

template <typename KeyType, typename ValueType>
Map<KeyType, ValueType>& Map<KeyType, ValueType>::putAll(const Map& map2) {
    for (const KeyType& key : map2) {
        put(key, map2.get(key));
    }
    return *this;
}

template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::remove(const KeyType& key) {
    _elements.erase(key);
    _version.update();
}

template <typename KeyType, typename ValueType>
Map<KeyType, ValueType>& Map<KeyType, ValueType>::removeAll(const Map& map2) {
    for (const KeyType& key : map2) {
        if (containsKey(key) && get(key) == map2.get(key)) {
            remove(key);
        }
    }
    return *this;
}

template <typename KeyType, typename ValueType>
Map<KeyType, ValueType>& Map<KeyType, ValueType>::retainAll(const Map& map2) {
    Vector<KeyType> toRemove;
    for (const KeyType& key : *this) {
        if (!map2.containsKey(key) || get(key) != map2.get(key)) {
            toRemove.add(key);
        }
    }
    for (const KeyType& key : toRemove) {
        remove(key);
    }
    return *this;
}

template <typename KeyType, typename ValueType>
int Map<KeyType, ValueType>::size() const {
    return _elements.size();
}

template <typename KeyType, typename ValueType>
std::string Map<KeyType, ValueType>::toString() const {
    std::ostringstream os;
    os << *this;
    return os.str();
}

template <typename KeyType,typename ValueType>
Vector<ValueType> Map<KeyType, ValueType>::values() const {
    Vector<ValueType> values;
    for (const auto& entry: _elements) {
        values.add(entry.second);
    }
    return values;
}

template <typename KeyType, typename ValueType>
ValueType& Map<KeyType, ValueType>::operator [](const KeyType& key) {
    auto presize = size();
    auto& result = _elements[key];

    /* 如果大小已更新，则一定插入了某个元素。 */
    if (presize != size()) _version.update();
    return result;
}

template <typename KeyType, typename ValueType>
ValueType Map<KeyType, ValueType>::operator [](const KeyType& key) const {
    return get(key);
}

template <typename KeyType, typename ValueType>
Map<KeyType, ValueType> Map<KeyType, ValueType>::operator +(const Map& map2) const {
    Map<KeyType, ValueType> result = *this;
    return result.putAll(map2);
}

template <typename KeyType, typename ValueType>
Map<KeyType, ValueType>& Map<KeyType, ValueType>::operator +=(const Map& map2) {
    return putAll(map2);
}

template <typename KeyType, typename ValueType>
Map<KeyType, ValueType> Map<KeyType, ValueType>::operator -(const Map& map2) const {
    Map<KeyType, ValueType> result = *this;
    return result.removeAll(map2);
}

template <typename KeyType, typename ValueType>
Map<KeyType, ValueType>& Map<KeyType, ValueType>::operator -=(const Map& map2) {
    return removeAll(map2);
}

template <typename KeyType, typename ValueType>
Map<KeyType, ValueType> Map<KeyType, ValueType>::operator *(const Map& map2) const {
    Map<KeyType, ValueType> result = *this;
    return result.retainAll(map2);
}

template <typename KeyType, typename ValueType>
Map<KeyType, ValueType>& Map<KeyType, ValueType>::operator *=(const Map& map2) {
    return retainAll(map2);
}

template <typename KeyType, typename ValueType>
bool Map<KeyType, ValueType>::operator ==(const Map& map2) const {
    return equals(map2);
}

template <typename KeyType, typename ValueType>
bool Map<KeyType, ValueType>::operator !=(const Map& map2) const {
    return !equals(map2);   // BUG 修复 2016/01/27，感谢 O. Zeng
}

template <typename KeyType, typename ValueType>
bool Map<KeyType, ValueType>::operator <(const Map& map2) const {
    return stanfordcpplib::collections::compareMaps(*this, map2) < 0;
}

template <typename KeyType, typename ValueType>
bool Map<KeyType, ValueType>::operator <=(const Map& map2) const {
    return stanfordcpplib::collections::compareMaps(*this, map2) <= 0;
}

template <typename KeyType, typename ValueType>
bool Map<KeyType, ValueType>::operator >(const Map& map2) const {
    return stanfordcpplib::collections::compareMaps(*this, map2) > 0;
}

template <typename KeyType, typename ValueType>
bool Map<KeyType, ValueType>::operator >=(const Map& map2) const {
    return stanfordcpplib::collections::compareMaps(*this, map2) >= 0;
}

template <typename KeyType, typename ValueType>
typename Map<KeyType, ValueType>::iterator Map<KeyType, ValueType>::begin() const {
    return iterator({ &_version, _elements.begin(), _elements });
}

template <typename KeyType, typename ValueType>
typename Map<KeyType, ValueType>::iterator Map<KeyType, ValueType>::end() const {
    return iterator({ &_version, _elements.end(), _elements });
}

/*
 * 实现说明：<< 和 >>
 * -------------------------------
 * 插入和提取运算符使用以下文件中的模板功能：
 * 使用 strlib.h 读写通用值，并以特殊方式处理字符串
 * 特殊处理。
 */
template <typename KeyType, typename ValueType>
std::ostream& operator <<(std::ostream& os,
                          const Map<KeyType, ValueType>& map) {
    return stanfordcpplib::collections::writeMap(os, map);
}

template <typename KeyType, typename ValueType>
std::istream& operator >>(std::istream& is, Map<KeyType,ValueType>& map) {
    KeyType key;
    ValueType value;
    return stanfordcpplib::collections::readPairedCollection(is, map, key, value, /* 描述符 */ std::string("Map::operator >>"));
}

/*
 * 映射的模板哈希函数。
 * 要求 Map 中的键和值类型具有 hashCode 函数。
 */
template <typename K, typename V>
int hashCode(const Map<K, V>& map) {
    return stanfordcpplib::collections::hashCodeMap(map);
}

/*
 * 函数：randomKey
 * 用法：element = randomKey(map);
 * --------------------------------
 * 从给定映射中随机选择并返回一个键。
 * 如果映射为空，则抛出错误。
 */
template <typename K, typename V>
const K& randomKey(const Map<K, V>& map) {
    return stanfordcpplib::collections::randomElement(map);
}

#endif // _map_h
