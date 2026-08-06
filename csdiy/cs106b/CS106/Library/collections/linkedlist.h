/*
 * 文件：linkedlist.h
 * ------------------
 * 此文件导出 <code>LinkedList</code> 类，该类提供
 * 对象双向链表的实现，并提供
 * 类似于 <code>Vector</code> 类的公共接口。
 */

#ifndef _linkedlist_h
#define _linkedlist_h

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <list>
#include <sstream>
#include <string>
#include <functional>

#include "collections.h"
#include "error.h"
#include "hashcode.h"
#include "random.h"
#include "strlib.h"
#include "vector.h"

/*
 * 类：LinkedList<ValueType>
 * ----------------------------
 * 此类存储一个类似数组的有序值列表。
 * 支持使用方括号进行传统数组选择，但
 * 还支持插入和删除元素。在以下方面类似：
 * 与 STL <code>list</code> 类型对应的函数。
 */
template <typename ValueType>
class LinkedList {
public:
    /*
     * 构造函数：LinkedList
     * 用法：LinkedList<ValueType> list;
     * ----------------------------------
     * 初始化一个新 LinkedList。默认构造函数创建一个
     * 空 LinkedList。
     */
    LinkedList() = default;
    /* 隐式 */ LinkedList(const std::list<ValueType>& v);

    /*
     * 此构造函数使用初始化列表设置链表。
     * 用法：LinkedList<int> list {1, 2, 3};
     */
    LinkedList(std::initializer_list<ValueType> list);

    /*
     * 析构函数：~LinkedList
     * -------------------
     * 释放此 LinkedList 分配的任何堆存储。
     */
    virtual ~LinkedList() = default;

    /*
     * 方法：add
     * 用法：list.add(value);
     * ----------------------
     * 将新值添加到此 LinkedList 末尾。
     */
    void add(ValueType value);

    /*
     * 方法：addAll
     * 用法：list.addAll(l2);
     * -----------------------
     * 将给定其他链表中的所有元素添加到此列表。
     * 返回对此列表的引用。
     * 行为与 += 运算符相同。
     */
    LinkedList<ValueType>& addAll(const LinkedList<ValueType>& list);

    /*
     * 方法：clear
     * 用法：list.clear();
     * --------------------
     * 从此 LinkedList 中删除所有元素。
     */
    void clear();

    /*
     * 方法：equals
     * 用法：if (list.equals(l2)) ...
     * -------------------------------
     * 如果此链表包含完全相同的内容，则返回 <code>true</code>
     * 与给定另一个列表相同的值。
     * 行为与 == 运算符相同。
     */
    bool equals(const LinkedList<ValueType>& l2) const;

    /*
     * 方法：get
     * 用法：ValueType val = list.get(index);
     * ---------------------------------------
     * 返回此 LinkedList 中指定索引处的元素。此
     * 如果索引不在链表范围内，此方法会报告错误。
     *
     * 客户端应注意，与向量不同，此操作
     * 对于链表为 O(N)，因为必须遍历列表才能到达
     * 给定索引。
     */
    const ValueType& get(int index) const;

    /*
     * 方法：insert
     * 用法：list.insert(0, value);
     * -----------------------------
     * 在指定索引之前将元素插入此 LinkedList。
     * 如果索引超出从 0 开始的范围，此方法会报告错误
     * 范围最大可包含 LinkedList 的长度。
     */
    void insert(int index, ValueType value);

    /*
     * 方法：isEmpty
     * 用法：if (list.isEmpty()) ...
     * ------------------------------
     * 如果此 LinkedList 不包含元素，则返回 <code>true</code>。
     */
    bool isEmpty() const;

    /*
     * 方法：mapAll
     * 用法：list.mapAll(fn);
     * ----------------------
     * 按以下顺序对 LinkedList 中的每个元素调用指定函数：
     * 按索引升序。
     */
    void mapAll(std::function<void (const ValueType &)> fn) const;

    /*
     * 方法：remove
     * 用法：list.remove(index);
     * -------------------------
     * 从此 LinkedList 中删除指定索引处的元素。
     * 如果索引超出列表范围，此方法会报告错误。
     */
    void remove(int index);

    /*
     * 方法：set
     * 用法：list.set(index, value);
     * ------------------------------
     * 用以下值替换此 LinkedList 中指定索引处的元素
     * 新值。该索引处之前的值会被覆盖。
     * 如果索引不在列表范围内，此方法会报告错误。
     *
     * 客户端应注意，与向量不同，此操作
     * 对于链表为 O(N)，因为必须遍历列表才能到达
     * 给定索引。
     */
    void set(int index, const ValueType& value);

    /*
     * 方法：size
     * 用法：int nElems = list.size();
     * --------------------------------
     * 返回此 LinkedList 中的元素数量。
     */
    int size() const;

    /*
     * 方法：sort
     * 用法：list.sort();
     * -------------------
     * 将此链表中的元素重新排列为排序顺序。
     * 例如，如果列表存储 {9, 1, 4, 3}，则将其改为 {1, 3, 4, 9}。
     * ValueType 必须具有 operator < 才能调用此方法。
     */
    void sort();

    /*
     * 方法：subList
     * 用法：LinkedList<ValueType> sub = list.subList(start, length);
     * ---------------------------------------------------------------
     * 返回一个包含给定元素子集范围的新列表
     * 从此列表生成。新列表是深拷贝，不与此列表链接。
     * 如果范围 (start .. start + length) 未包含在
     * 位于此列表的边界内，否则 length 为负数。
     */
    LinkedList<ValueType> subList(int start, int length) const;

    /*
     * 方法：toString
     * 用法：string str = list.toString();
     * ------------------------------------
     * 将 LinkedList 转换为可打印的字符串表示。
     */
    std::string toString() const;

    /*
     * 运算符：[]
     * 用法：list[index]
     * -----------------
     * 重载 <code>[]</code>，用于从此 LinkedList 中选择元素。
     * 此扩展允许使用传统数组下标语法来
     * 获取或设置单个元素。若以下情况发生，此方法会报错：
     * 索引超出列表范围。该文件支持两种
     * 此运算符的多个版本，一个用于 <code>const</code> LinkedList，另一个
     * 一个用于可变 LinkedList。
     *
     * 客户端应注意，此操作对于链表是 O(N)
     * 链表，因为它必须遍历链表才能到达给定索引。
     */
    ValueType& operator [](int index);
    const ValueType& operator [](int index) const;

    /*
     * 运算符：+
     * 用法：v1 + l2
     * --------------
     * 连接两个 LinkedList，或将此链表与一个
     * 例如 {1, 2, 3} 的初始化列表。
     */
    LinkedList operator +(const LinkedList& l2) const;
    LinkedList operator +(std::initializer_list<ValueType> list) const;

    /*
     * 运算符：+=
     * 用法：l1 += l2;
     *        l1 += value;
     * -------------------
     * 将 <code>l2</code> 中的所有元素（或单个
     * 将指定值）添加到 <code>l1</code>。为方便起见，
     * <code>LinkedList</code> 包还重载了逗号运算符，因此
     * 使得可以像这样初始化 LinkedList：
     *
     *<pre>
     *    LinkedList&lt;int&gt; digits;
     *    digits += 0, 1, 2, 3, 4, 5, 6, 7, 8, 9;
     *</pre>
     */
    LinkedList& operator +=(const LinkedList& l2);
    LinkedList& operator +=(const ValueType& value);

    /*
     * 比较 LinkedList 是否相等。
     */
    bool operator ==(const LinkedList& list2) const;
    bool operator !=(const LinkedList& list2) const;


    /*
     * 运算符：<、>、<=、>=
     * 用法：if (list1 == list2) ...
     * ...
     * -------------------------------
     * 用于比较两个链表的关系运算符。
     * <、>、<=、>= 运算符要求 ValueType 定义 < 运算符
     * 以便逐对比较各元素。
     */
    bool operator <(const LinkedList& list2) const;
    bool operator <=(const LinkedList& list2) const;
    bool operator >(const LinkedList& list2) const;
    bool operator >=(const LinkedList& list2) const;

    /*
     * 其他 LinkedList 操作
     * --------------------------------
     * 除本接口中列出的方法外，LinkedList
     * 类支持以下操作：
     *
     *   - 使用 << 和 >> 运算符进行流输入/输出
     *   - 为复制构造函数和赋值运算符实现深拷贝
     *   - 使用基于范围的 for 语句或 STL 迭代器进行迭代
     *
     * 这些迭代形式按索引顺序处理 LinkedList。
     */

    /* 私有部分 */

    /**********************************************************************/
    /* 注意：文件中此处以下的所有内容在逻辑上都属于    */
    /* 属于实现细节，客户端无需关注。    */
    /**********************************************************************/

private:
    /*
     * 实现说明：LinkedList 数据结构
     * -------------------------------------------
     * LinkedList 的元素存储在动态数组中
     * 指定的元素类型。如果数组中的空间曾经
     * 容量耗尽时，实现会将数组容量加倍。
     */

    /* 实例变量 */
    std::list<ValueType> _elements;   // 使用 STL 链表作为底层存储
    stanfordcpplib::collections::VersionTracker _version;

    /* 私有方法 */

    /*
     * 如果给定索引不在以下范围内，则抛出 ErrorException：
     * [min..max]，包含两端。
     * 这是供 LinkedList 各成员使用的统一错误处理程序，这些成员
     * 接受索引参数。
     * prefix 参数表示放在以下内容开头的文本字符串：
     * 错误消息，通常用于指出是哪个成员抛出了错误。
     *
     * 我们将 prefix 设为 const char* 而不是 std::string，以避免必须
     * 每次调用都构造并销毁前缀。
     */
    void checkIndex(int index, int min, int max, const char* prefix) const;

    /*
     * 隐藏功能
     * ---------------
     * 此文件的剩余部分包含实现以下功能所需的代码：
     * 支持深拷贝和迭代。加入这些方法
     * 放入公共接口会使该接口更加
     * 普通客户端难以理解。
     */

public:

    /*
     * 运算符：,
     * -----------
     * 将元素添加到作为左操作数传入的 LinkedList。
     * 此形式使在旧版 C++ 中初始化 LinkedList 更方便。
     */
    LinkedList& operator ,(const ValueType& value);

    /*
     * 迭代器支持。
     */
    using iterator = stanfordcpplib::collections::CheckedIterator<typename std::list<ValueType>::iterator>;
    using const_iterator = stanfordcpplib::collections::CheckedIterator<typename std::list<ValueType>::const_iterator>;

    iterator begin() {
        return { &_version, _elements.begin(), _elements };
    }
    iterator end() {
        return { &_version, _elements.end(), _elements };
    }
    const_iterator begin() const {
        return { &_version, _elements.begin(), _elements };
    }
    const_iterator end() const {
        return { &_version, _elements.end(), _elements };
    }
};

/* 实现部分 */

template <typename ValueType>
LinkedList<ValueType>::LinkedList(const std::list<ValueType>& v)
        : _elements(v) {
    // 空
}

template <typename ValueType>
LinkedList<ValueType>::LinkedList(std::initializer_list<ValueType> list) : _elements(list) {
    // 空
}

template <typename ValueType>
void LinkedList<ValueType>::add(ValueType value) {
    _elements.push_back(value);
    _version.update();
}

template <typename ValueType>
LinkedList<ValueType>&
LinkedList<ValueType>::addAll(const LinkedList<ValueType>& list) {
    for (const ValueType& value : list) {
        add(value);
    }
    _version.update();
    return *this;
}

template <typename ValueType>
void LinkedList<ValueType>::clear() {
    _elements.clear();
    _version.update();
}


template <typename ValueType>
bool LinkedList<ValueType>::equals(const LinkedList<ValueType>& list2) const {
    return _elements == list2._elements;
}


template <typename ValueType>
const ValueType & LinkedList<ValueType>::get(int index) const {
    checkIndex(index, 0, size()-1, "get");
    return *std::next(_elements.begin(), index);
}

template <typename ValueType>
void LinkedList<ValueType>::insert(int index, ValueType value) {
    checkIndex(index, 0, size(), "insert");
    auto itr = _elements.begin();
    std::advance(itr, index);
    _elements.insert(itr, value);
    _version.update();
}

template <typename ValueType>
bool LinkedList<ValueType>::isEmpty() const {
    return _elements.empty();
}

/*
 * 实现说明：mapAll
 * ----------------------------
 * mapAll 函数的各种版本会应用该函数或
 * 按索引升序对每个元素调用函数对象。
 */
template <typename ValueType>
void LinkedList<ValueType>::mapAll(std::function<void (const ValueType &)> fn) const {
    for (ValueType element : *this) {
        fn(element);
    }
}

template <typename ValueType>
void LinkedList<ValueType>::remove(int index) {
    checkIndex(index, 0, size()-1, "remove");
    auto itr = _elements.begin();
    advance(itr, index);
    _elements.erase(itr);
    _version.update();
}

template <typename ValueType>
void LinkedList<ValueType>::set(int index, const ValueType & value) {
    checkIndex(index, 0, size()-1, "set");
    (*this)[index] = value;
}

template <typename ValueType>
int LinkedList<ValueType>::size() const {
    return _elements.size();
}


template <typename ValueType>
void LinkedList<ValueType>::sort() {
    // 实际对向量排序，以避免 O(N^2) 运行时间
    // 代价是额外使用 O(N) 内存
    Vector<ValueType> vec;
    for (ValueType element : *this) {
        vec.add(element);
    }
    std::sort(vec.begin(), vec.end());

    clear();
    for (const ValueType& element : vec) {
        add(element);
    }
}

template <typename ValueType>
LinkedList<ValueType> LinkedList<ValueType>::subList(int start, int length) const {
    checkIndex(start, 0, size(), "subList");
    checkIndex(start + length, 0, size(), "subList");
    if (length < 0) {
        error("LinkedList::subList: length cannot be negative");
    }
    LinkedList<ValueType> result;
    auto itr = begin();
    for (int i = 0; i < start; i++) {
        ++itr;
    }
    for (int i = 0; i < length; i++) {
        result.add(*itr);
        ++itr;
    }
    return result;
}

template <typename ValueType>
std::string LinkedList<ValueType>::toString() const {
    std::ostringstream os;
    os << *this;
    return os.str();
}

/*
 * 实现说明：LinkedList 选择
 * ------------------------------------------
 * 以下代码使用以下方式实现传统数组选择：
 * 用于索引的方括号。
 */
template <typename ValueType>
ValueType& LinkedList<ValueType>::operator [](int index) {
    checkIndex(index, 0, size()-1, "operator []");
    auto itr = begin();
    advance(itr, index);
    return *itr;
}
template <typename ValueType>
const ValueType& LinkedList<ValueType>::operator [](int index) const {
    checkIndex(index, 0, size()-1, "operator []");
    auto itr = begin();
    advance(itr, index);
    return *itr;
}

template <typename ValueType>
LinkedList<ValueType>
LinkedList<ValueType>::operator +(const LinkedList& list2) const {
    LinkedList<ValueType> list = *this;
    return list.addAll(list2);
}

template <typename ValueType>
LinkedList<ValueType> LinkedList<ValueType>::operator +(std::initializer_list<ValueType> list) const {
    LinkedList<ValueType> result = *this;
    return result.addAll(list);
}

template <typename ValueType>
LinkedList<ValueType>&
LinkedList<ValueType>::operator +=(const LinkedList& list2) {
    return addAll(list2);
}

template <typename ValueType>
LinkedList<ValueType>&
LinkedList<ValueType>::operator +=(const ValueType& value) {
    add(value);
    return *this;
}

/*
 * 实现说明：关系运算符
 * 这些运算符只是转发到底层 STL list。
 */
template <typename ValueType>
bool LinkedList<ValueType>::operator ==(const LinkedList& list2) const {
    return _elements == list2._elements;
}

template <typename ValueType>
bool LinkedList<ValueType>::operator !=(const LinkedList& list2) const {
    return _elements != list2._elements;
}

template <typename ValueType>
bool LinkedList<ValueType>::operator <(const LinkedList& list2) const {
    return _elements < list2._elements;
}

template <typename ValueType>
bool LinkedList<ValueType>::operator <=(const LinkedList& list2) const {
    return _elements <= list2._elements;
}

template <typename ValueType>
bool LinkedList<ValueType>::operator >(const LinkedList& list2) const {
    return _elements > list2._elements;
}

template <typename ValueType>
bool LinkedList<ValueType>::operator >=(const LinkedList& list2) const {
    return this->_elements >= list2._elements;
}

template <typename ValueType>
void LinkedList<ValueType>::checkIndex(int index, int min, int max, const char* prefix) const {
    if (index < min || index > max) {
        std::ostringstream out;
        out << "LinkedList::" << prefix << ": index of " << index
            << " is outside of valid range [";
        if (min < max) {
            out << min << ".." << max;
        } else if (min == max) {
            out << min;
        } // 否则 min > max，没有范围，空 LinkedList
        out << "]";
        error(out.str());
    }
}

/*
 * 实现说明：逗号运算符
 * ------------------------------------
 * 逗号运算符通过将右操作数添加到 LinkedList 来工作，并
 * 然后按引用返回 LinkedList，以便为下一次
 * 链中的值。
 */
template <typename ValueType>
LinkedList<ValueType>&
LinkedList<ValueType>::operator ,(const ValueType& value) {
    add(value);
    return *this;
}

/*
 * 实现说明：<< 和 >>
 * -------------------------------
 * 插入和提取运算符使用以下文件中的模板功能：
 * 使用 strlib.h 读写通用值，并以特殊方式处理字符串
 * 特殊处理。
 */
template <typename ValueType>
std::ostream& operator <<(std::ostream& os, const LinkedList<ValueType>& list) {
    return stanfordcpplib::collections::writeCollection(os, list);
}

template <typename ValueType>
std::istream& operator >>(std::istream& is, LinkedList<ValueType>& list) {
    ValueType element;
    return stanfordcpplib::collections::readCollection(is, list, element, /* 描述符 */ "LinkedList::operator >>");
}

/*
 * 链表的模板哈希函数。
 * 要求 LinkedList 中的元素类型具有 hashCode 函数。
 */
template <typename T>
int hashCode(const LinkedList<T>& list) {
    return stanfordcpplib::collections::hashCodeCollection(list);
}

/*
 * 函数：randomElement
 * 用法：element = randomElement(list);
 * -------------------------------------
 * 返回从给定列表中随机选择的元素。
 * 如果列表为空，则抛出错误。
 */
template <typename T>
const T& randomElement(const LinkedList<T>& list) {
    return stanfordcpplib::collections::randomElementIndexed(list);
}

#endif // _linkedlist_h
