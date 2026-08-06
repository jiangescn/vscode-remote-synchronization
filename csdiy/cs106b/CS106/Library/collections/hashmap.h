/*
 * 文件：hashmap.h
 * ---------------
 * 此文件导出 <code>HashMap</code> 类，该类存储
 * 一组<i>键</i>-<i>值</i>对。
 */

#ifndef _hashmap_h
#define _hashmap_h

#include <cstdlib>
#include <initializer_list>
#include <string>
#include <utility>
#include <unordered_map>
#include <functional>

#include "collections.h"
#include "error.h"
#include "hashcode.h"
#include "vector.h"

/*
 * 类：HashMap<KeyType,ValueType>
 * ---------------------------------
 * 此类实现了
 * <b><i>键</i></b>和<b><i>值</i></b>。此类
 * 与 <a href="Map-class.html"><code>Map</code></a> 类相同
 * 区别仅在于它使用哈希表作为底层
 * 表示。尽管 <code>HashMap</code> 类以
 * 在常数时间内，<code>HashMap</code> 的迭代器返回
 * 以看似随机的顺序排列的值。
 */
template <typename KeyType, typename ValueType>
class HashMap {
public:
    /*
     * 构造函数：HashMap
     * 用法：HashMap<KeyType,ValueType> map;
     * --------------------------------------
     * 初始化一个新的空映射，用于关联以下类型的键和值
     * 指定的类型。用作键的类型必须定义
     * <code>==</code> 运算符，并且必须有一个自由函数
     * 具有以下签名：
     *
     *<pre>
     *    int hashCode(KeyType key);
     *</pre>
     *
     * 返回由键决定的正整数。此接口
     * 导出用于 <code>string</code> 和以下类型的 <code>hashCode</code> 函数
     * C++ 基本类型。
     */
    HashMap() = default;

    /*
     * 构造函数：HashMap
     * 用法：HashMap<ValueType> map {{"a", 1}, {"b", 2}, {"c", 3}};
     * -------------------------------------------------------------
     * 初始化存储给定键值对的新映射。
     * 请注意，键值对在内部以不可预测的顺序存储，而不是
     * 不一定与它们在初始化列表中的书写顺序相同。
     */
    HashMap(std::initializer_list<std::pair<const KeyType, ValueType>> list);

    /*
     * 析构函数：~HashMap
     * --------------------
     * 释放与此映射关联的所有堆存储。
     */
    virtual ~HashMap() = default;

    /*
     * 方法：lastKey
     * 用法：KeyType value = map.lastKey();
     * ------------------------------------
     * 按照以下方式建立的顺序返回映射中的最后一个键：
     * <code>for-each</code> 循环。
     * 请注意，由于键的存储顺序不可预测，
     * 这不一定等于任何特定意义上“最大”的键值
     * 排序顺序；它只是恰好最后输出的键
     * 来自 for-each 循环。
     * 若映射为空，则产生错误。
     */
    KeyType lastKey() const;

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
    bool equals(const HashMap& map2) const;

    /*
     * 方法：firstKey
     * 用法：KeyType value = map.firstKey();
     * -------------------------------------
     * 按照以下方式建立的顺序返回映射中的第一个键：
     * <code>for-each</code> 循环。
     * 请注意，由于键的存储顺序不可预测，
     * 这不一定等于任何特定意义上“最小”的键值
     * 排序顺序；它只是恰好最先输出的键
     * 来自 for-each 循环。
     * 若映射为空，则产生错误。
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
     * 方法：mapAll
     * 用法：map.mapAll(fn);
     * ----------------------
     * 遍历映射条目，并调用 <code>fn(key, value)</code>
     * 分别处理每一个。键按不确定顺序处理。
     */
    void mapAll(std::function<void(const KeyType&, const ValueType&)> fn) const;

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
     * ---------------------------
     * 将给定映射中的所有键值对添加到此映射。
     * 若两个映射包含相同键的键值对，则采用 map2 中的
     * 替换此映射中的对应项。
     * 还可以传入由键值对组成的初始化列表，例如 {{"a", 1}, {"b", 2}, {"c", 3}}。
     * 返回对此映射的引用。
     */
    HashMap& putAll(const HashMap& map2);

    /*
     * 方法：remove
     * 用法：map.remove(key);
     * -----------------------
     * 从此映射中移除 <code>key</code> 的任何条目。
     * 如果找不到给定键，则不产生任何效果。
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
    HashMap& removeAll(const HashMap& map2);

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
    HashMap& retainAll(const HashMap& map2);

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
     * 运算符：+
     * 用法：map1 + map2
     * ------------------
     * 返回两个映射的并集，等价于第一个映射的副本
     * 等价于在第一个映射上调用 putAll，并将第二个映射作为参数传入。
     * 若两个映射都包含同一键的映射关系，则
     * 优先采用第二个映射中的值。
     * 还可以传入由键值对组成的初始化列表，例如 {{"a", 1}, {"b", 2}, {"c", 3}}。
     */
    HashMap operator +(const HashMap& map2) const;

    /*
     * 运算符：+=
     * 用法：map1 += map2;
     * --------------------
     * 将给定映射中的所有键值对添加到此映射。
     * 等价于调用 putAll(map2)。
     * 还可以传入由键值对组成的初始化列表，例如 {{"a", 1}, {"b", 2}, {"c", 3}}。
     */
    HashMap& operator +=(const HashMap& map2);

    /*
     * 运算符：-
     * 用法：map1 - map2
     * ------------------
     * 返回两个映射的差集，等价于第一个映射的副本
     * 等价于在第一个映射上调用 removeAll，并将第二个映射作为参数传入。
     * 还可以传入由键值对组成的初始化列表，例如 {{"a", 1}, {"b", 2}, {"c", 3}}。
     */
    HashMap operator -(const HashMap& map2) const;

    /*
     * 运算符：-=
     * 用法：map1 -= map2;
     * --------------------
     * 从此映射中移除给定映射中的所有键/值对。
     * 等价于调用 removeAll(map2)。
     * 还可以传入由键值对组成的初始化列表，例如 {{"a", 1}, {"b", 2}, {"c", 3}}。
     */
    HashMap& operator -=(const HashMap& map2);

    /*
     * 运算符：*
     * 用法：map1 * map2
     * ------------------
     * 返回两个映射的交集，等价于第一个映射的副本
     * 等价于在第一个映射上调用 retainAll，并将第二个映射作为参数传入。
     * 还可以传入由键值对组成的初始化列表，例如 {{"a", 1}, {"b", 2}, {"c", 3}}。
     */
    HashMap operator *(const HashMap& map2) const;

    /*
     * 运算符：*=
     * 用法：map1 *= map2;
     * ---------------------
     * 从此映射中移除给定映射中找不到的所有键/值对。
     * 等价于调用 retainAll(map2)。
     * 还可以传入由键值对组成的初始化列表，例如 {{"a", 1}, {"b", 2}, {"c", 3}}。
     */
    HashMap& operator *=(const HashMap& map2);

    /*
     * 其他 HashMap 操作
     * -----------------------------
     * 除本接口中列出的方法外，HashMap
     * 类支持以下操作：
     *
     *   - 使用 << 和 >> 运算符进行流输入/输出
     *   - 为复制构造函数和赋值运算符实现深拷贝
     *   - 使用基于范围的 for 语句和 STL 迭代器进行迭代
     *
     * HashMap 类不保证迭代顺序。
     */

    /* 私有部分 */

    /**********************************************************************/
    /* 注意：文件中此处以下的所有内容在逻辑上都属于    */
    /* 属于实现细节，客户端无需关注。    */
    /**********************************************************************/

private:
    static_assert(stanfordcpplib::collections::IsHashable<KeyType>::value,
                  "Oops! You tried using a type as a key in our HashMap without making it hashable. Click this error for more details.");
    /*
     * CS106 的同学你好！如果编译错误将你指向此行代码，
     * 这可能意味着你尝试使用自定义结构体或类类型创建 HashMap
     * 作为键类型，或将自定义结构体作为值类型的 HashSet。
     *
     * 要让某类型成为 HashMap 的键类型——或成为其值类型
     * 在 HashSet 中——它需要定义 hashCode 函数，并且能够被
     * 使用 == 运算符比较。如果你被引导到这里，则这两个条件之一
     * 未满足。
     *
     * 有两种修复方式。第一种是直接不使用自定义
     * 将该类型用作 HashMap 的键或 HashSet 的值。这可能是最简单的选择。
     *
     * 第二种修复方式是显式定义 hashCode() 和 operator== 函数
     * 为你的类型定义。首先按如下方式定义 hashCode：
     *
     *     int hashCode(const YourCustomType& obj) {
     *         return hashCode(obj.data1, obj.data2, ..., obj.dataN);
     *     }
     *
     * 其中 data1、data2、...、dataN 是该类型的数据成员。例如，如果你有
     * 自定义类型
     *
     *     struct MyType {
     *         int myInt;
     *         string myString;
     *     };
     *
     * 你需要定义函数
     *
     *     int hashCode(const MyType& obj) {
     *         return hashCode(obj.myInt, obj.myString);
     *     }
     *
     * 其次，按如下方式定义 operator==：
     *
     *     bool operator== (const YourCustomType& lhs, const YourCustomType& rhs) {
     *         return lhs.data1 == rhs.data1 &&
     *                lhs.data2 == rhs.data2 &&
     *                         ...
     *                lhs.dataN == rhs.dataN;
     *     }
     *
     * 使用上面的 MyType 示例，我们会编写
     *
     *     bool operator== (const MyType& lhs, const MyType& rhs) {
     *         return lhs.myInt == rhs.myInt && lhs.myString == rhs.myString;
     *     }
     *
     * 希望这能有所帮助！
     */

    struct Hasher {
        std::size_t operator()(const KeyType& key) const {
            return hashCode(key);
        }
    };

    std::unordered_map<KeyType, ValueType, Hasher> _elements;
    stanfordcpplib::collections::VersionTracker _version;

    /* 私有方法 */

public:
    /*
     * 隐藏功能
     * ---------------
     * 此文件的剩余部分包含实现以下功能所需的代码：
     * 支持深拷贝和迭代。加入这些方法
     * 放入公共接口会使该接口更加
     * 普通客户端难以理解。
     */

    /*
     * 迭代器支持
     */

    using const_iterator = stanfordcpplib::collections::ProjectingIterator<stanfordcpplib::collections::CheckedIterator<typename std::unordered_map<KeyType, ValueType, Hasher>::const_iterator>>;
    using iterator = const_iterator;

    iterator begin() const;
    iterator end() const;

    /*
     * 哈希支持。
     */
    bool operator== (const HashMap& rhs) const;
    bool operator!= (const HashMap& rhs) const;

    template <typename K, typename V>
    friend int hashCode(const HashMap<K, V>& map);
};

template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType>::HashMap(std::initializer_list<std::pair<const KeyType, ValueType>> list)
        : _elements(list) {
}

template <typename KeyType, typename ValueType>
KeyType HashMap<KeyType, ValueType>::lastKey() const {
    if (isEmpty()) {
        error("HashMap::lastKey: map is empty");
    }

    return std::next(_elements.begin(), _elements.size() - 1)->first;
}

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::clear() {
    _elements.clear();
    _version.update();
}

template <typename KeyType, typename ValueType>
bool HashMap<KeyType, ValueType>::containsKey(const KeyType& key) const {
    return !!_elements.count(key);
}

template <typename KeyType, typename ValueType>
bool HashMap<KeyType, ValueType>::equals(const HashMap<KeyType, ValueType>& map2) const {
    return stanfordcpplib::collections::equalsMap(*this, map2);
}

template <typename KeyType, typename ValueType>
KeyType HashMap<KeyType, ValueType>::firstKey() const {
    if (isEmpty()) {
        error("HashMap::firstKey: map is empty");
    }
    return *begin();
}

template <typename KeyType, typename ValueType>
ValueType HashMap<KeyType, ValueType>::get(const KeyType& key) const {
    auto itr = _elements.find(key);
    return itr == _elements.end()? ValueType() : itr->second;
}

template <typename KeyType, typename ValueType>
bool HashMap<KeyType, ValueType>::isEmpty() const {
    return _elements.empty();
}

template <typename KeyType, typename ValueType>
Vector<KeyType> HashMap<KeyType, ValueType>::keys() const {
    Vector<KeyType> keyset;
    for (const auto& entry: _elements) {
        keyset.add(entry.first);
    }
    return keyset;
}

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::mapAll(std::function<void (const KeyType&, const ValueType&)> fn) const {
    for (const auto& entry: _elements) {
        fn(entry.first, entry.second);
    }
}

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::put(const KeyType& key, const ValueType& value) {
    int presize = size();
    _elements[key] = value;

    if (presize != size()) _version.update();
}

template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType>& HashMap<KeyType, ValueType>::putAll(const HashMap& map2) {
    for (const KeyType& key : map2) {
        put(key, map2.get(key));
    }
    return *this;
}

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::remove(const KeyType& key) {
    auto itr = _elements.find(key);
    if (itr != _elements.end()) {
        _elements.erase(itr);
        _version.update();
    }
}

template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType>& HashMap<KeyType, ValueType>::removeAll(const HashMap& map2) {
    for (const KeyType& key : map2) {
        if (containsKey(key) && get(key) == map2.get(key)) {
            remove(key);
        }
    }
    return *this;
}

template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType>& HashMap<KeyType, ValueType>::retainAll(const HashMap& map2) {
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
int HashMap<KeyType, ValueType>::size() const {
    return _elements.size();
}

template <typename KeyType, typename ValueType>
std::string HashMap<KeyType, ValueType>::toString() const {
    std::ostringstream os;
    os << *this;
    return os.str();
}

template <typename KeyType, typename ValueType>
Vector<ValueType> HashMap<KeyType, ValueType>::values() const {
    Vector<ValueType> values;
    for (const auto& entry: _elements) {
        values.add(entry.second);
    }
    return values;
}

template <typename KeyType, typename ValueType>
ValueType& HashMap<KeyType, ValueType>::operator [](const KeyType& key) {
    int presize = size();
    ValueType& result = _elements[key];

    if (presize != size()) _version.update();
    return result;
}

template <typename KeyType, typename ValueType>
ValueType HashMap<KeyType, ValueType>::operator [](const KeyType& key) const {
    return get(key);
}

template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType> HashMap<KeyType, ValueType>::operator +(const HashMap& map2) const {
    HashMap<KeyType, ValueType> result = *this;
    return result.putAll(map2);
}

template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType>& HashMap<KeyType, ValueType>::operator +=(const HashMap& map2) {
    return putAll(map2);
}

template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType> HashMap<KeyType, ValueType>::operator -(const HashMap& map2) const {
    HashMap<KeyType, ValueType> result = *this;
    return result.removeAll(map2);
}

template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType>& HashMap<KeyType, ValueType>::operator -=(const HashMap& map2) {
    return removeAll(map2);
}

template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType> HashMap<KeyType, ValueType>::operator *(const HashMap& map2) const {
    HashMap<KeyType, ValueType> result = *this;
    return result.retainAll(map2);
}

template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType>& HashMap<KeyType, ValueType>::operator *=(const HashMap& map2) {
    return retainAll(map2);
}

template <typename KeyType, typename ValueType>
typename HashMap<KeyType, ValueType>::iterator HashMap<KeyType, ValueType>::begin() const {
    return iterator({ &_version, _elements.begin(), _elements });
}

template <typename KeyType, typename ValueType>
typename HashMap<KeyType, ValueType>::iterator HashMap<KeyType, ValueType>::end() const {
    return iterator({ &_version, _elements.end(), _elements });
}

template <typename KeyType, typename ValueType>
bool HashMap<KeyType, ValueType>::operator == (const HashMap<KeyType, ValueType>& rhs) const {
    return stanfordcpplib::collections::equalsMap(*this, rhs);
}

template <typename KeyType, typename ValueType>
bool HashMap<KeyType, ValueType>::operator != (const HashMap<KeyType, ValueType>& rhs) const {
    return !(*this == rhs);
}

template <typename KeyType, typename ValueType>
int hashCode(const HashMap<KeyType, ValueType>& map) {
    return stanfordcpplib::collections::hashCodeMap(map, false);
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
                          const HashMap<KeyType, ValueType>& map) {
    return stanfordcpplib::collections::writeMap(os, map);
}

template <typename KeyType, typename ValueType>
std::istream& operator >>(std::istream& is,
                          HashMap<KeyType, ValueType>& map) {
    KeyType key;
    ValueType value;
    return stanfordcpplib::collections::readPairedCollection(is, map, key, value, /* 描述符 */ std::string("HashMap::operator >>"));
}

/*
 * 函数：randomKey
 * 用法：element = randomKey(map);
 * --------------------------------
 * 从给定映射中随机选择并返回一个键。
 * 如果映射为空，则抛出错误。
 */
template <typename K, typename V>
const K& randomKey(const HashMap<K, V>& map) {
    return stanfordcpplib::collections::randomElement(map);
}

#endif // _hashmap_h
