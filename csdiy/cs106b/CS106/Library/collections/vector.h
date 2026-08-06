/*
 * 文件：vector.h
 * --------------
 * 此文件导出 <code>Vector</code> 类，该类提供
 * C++ 数组类型的高效、安全、便捷替代品。
 */

#ifndef _vector_h
#define _vector_h

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <type_traits>
#include <functional>

#include "collections.h"
#include "error.h"
#include "hashcode.h"
#include "random.h"

/**
 * 此类存储一个类似数组的有序值列表。
 * 支持使用方括号进行传统数组选择，但
 * 还支持插入和删除元素。在以下方面类似：
 * 与 STL <code>vector</code> 类型对应的函数，但在两方面更简单
 * 使用和实现。
 */
template <typename ValueType>
class Vector {
public:
    /**
     * 初始化一个新的空向量。
     * @bigoh O(1)
     */
    Vector() = default;

    /**
     * 初始化一个新向量，创建包含 <code>n</code> 个元素的数组
     * 元素，每个元素都初始化为 <code>value</code>。
     * 如果缺少 <code>value</code>，元素将初始化为
     * 恢复为该类型的默认值。
     * @bigoh O(N)
     */
    explicit Vector(int n, ValueType value = ValueType());

    /**
     * 使用初始化列表设置 Vector。
     * @bigoh O(N)
     */
    Vector(std::initializer_list<ValueType> list);

    /**
     * 释放此向量分配的任何堆存储。
     * @bigoh O(1)
     */
    virtual ~Vector() = default;

    /**
     * 将新值添加到此向量末尾。
     * @bigoh O(1)
     */
    void add(const ValueType& value);

    /**
     * 将给定其他向量中的所有元素添加到此向量。
     * 返回对此向量的引用。
     * 行为与 += 运算符相同。
     * @bigoh O(N)
     */
    Vector<ValueType>& addAll(const Vector<ValueType>& v);

    /**
     * 从此向量中删除所有元素。
     * @bigoh O(1)
     */
    void clear();

    /**
     * 比较两个向量是否相等。
     * 如果此向量包含完全相同的内容，则返回 <code>true</code>
     * 与给定另一个 Vector 相同的值。
     * 行为与 == 运算符相同。
     * @bigoh O(N)
     */
    bool equals(const Vector<ValueType>& v) const;

    /**
     * 返回此向量中指定索引处的元素。
     * 行为与 [] 运算符类似。
     * @throw 如果索引不在数组范围内，则抛出 ErrorException
     * @bigoh O(1)
     */
    const ValueType& get(int index) const;

    /**
     * 在指定索引之前将元素插入此向量。
     * 后续所有元素向右移动一个位置。
     * @throw 如果索引不在从 0 开始的数组范围内，则抛出 ErrorException
     * 范围最大可包含 Vector 的长度。
     * @bigoh O(N)
     */
    void insert(int index, const ValueType& value);

    /**
     * 如果此向量不包含元素，则返回 <code>true</code>。
     * @bigoh O(1)
     */
    bool isEmpty() const;

    /**
     * 按以下顺序对向量中的每个元素调用指定函数：
     * 按索引升序。
     * @bigoh O(N)
     */
    void mapAll(std::function<void (const ValueType&)> fn) const;

    /**
     * 从此向量中删除指定索引处的元素
     * 并返回它。后续所有元素向
     * 左侧位置。
     * @throw 如果索引不在数组范围内，则抛出 ErrorException
     * @bigoh O(N)
     */
    ValueType remove(int index);

    /**
     * 用以下值替换此向量中指定索引处的元素
     * 新值。该索引处之前的值会被覆盖。
     * 行为与 [] 运算符类似。
     * @throw 如果索引不在数组范围内，则抛出 ErrorException
     * @bigoh O(1)
     */
    void set(int index, const ValueType& value);

    /**
     * 返回此向量中的元素数量。
     * @bigoh O(1)
     */
    int size() const;

    /**
     * 将此向量中的元素重新排列为排序顺序。
     * 例如，如果向量存储 {9, 1, 4, 3}，则将其改为 {1, 3, 4, 9}。
     * ValueType 必须具有 operator < 才能调用此方法。
     * @bigoh O(N log N)
     */
    void sort();

    /**
     * 返回一个包含给定元素子集范围的新向量
     * 从此向量生成。新向量是深拷贝，不与此向量链接。
     * @throw 如果范围 (start .. start + length) 不在有效范围内，则抛出 ErrorException
     *        位于此 Vector 的边界内，否则 length 为负数
     * @bigoh O(N)
     */
    Vector<ValueType> subList(int start, int length) const;

    /**
     * 返回一个包含从起始位置开始的元素的新向量
     * 到 Vector 末尾。
     *
     * @throw 如果 start > size()，则抛出 ErrorException
     * @bigoh O(N)
     */
    Vector<ValueType> subList(int start) const;

    /**
     * 将向量转换为可打印的字符串表示
     * 例如 "{10, 20, 30, 40}"。
     * @bigoh O(N)
     */
    std::string toString() const;

    /**
     * 重载 <code>[]</code>，用于从此向量中选择元素。
     * 此扩展允许使用传统数组下标语法来
     * 获取或设置单个元素。
     * @throw 如果索引不在数组范围内，则抛出 ErrorException
     * @bigoh O(1)
     */
    ValueType& operator [](int index);

    /**
     * 重载 <code>[]</code>，用于从此向量中选择元素。
     * 此扩展允许使用传统数组下标语法来
     * 获取或设置单个元素。
     * @throw 如果索引不在数组范围内，则抛出 ErrorException
     * @bigoh O(1)
     */
    const ValueType& operator [](int index) const;

    /**
     * 连接两个向量并返回结果。
     * @bigoh O(N)
     */
    Vector operator +(const Vector& v2) const;

    /**
     * 返回一个由此向量追加给定元素形成的新向量。
     * @bigoh O(N)
     */
    Vector operator +(const ValueType& elem) const;

    /**
     * 将 <code>v2</code> 中的所有元素添加到此向量末尾。
     * @bigoh O(N)
     */
    Vector& operator +=(const Vector& v2);

    /**
     * 将指定的单个值）添加到向量末尾。
     * @bigoh O(1)
     */
    Vector& operator +=(const ValueType& value);


    /**
     * 比较两个向量是否相等。
     * ValueType 必须具有 == 运算符。
     * @bigoh O(N)
     */
    bool operator ==(const Vector& v2) const;

    /**
     * 比较两个向量是否不相等。
     * ValueType 必须具有 != 运算符。
     * @bigoh O(N)
     */
    bool operator !=(const Vector& v2) const;

    /**
     * 用于比较两个向量的关系运算符。
     * 每个元素都与以下位置的对应元素逐对比较：
     * 另一个向量中相同索引处的元素；例如，先检查以下值：
     * 索引依次为 0、1，依此类推。
     * <、>、<=、>= 运算符要求 ValueType 定义 < 运算符
     * 以便逐对比较各元素。
     * @bigoh O(N)
     */
    bool operator <(const Vector& v2) const;

    /**
     * 用于比较两个向量的关系运算符。
     * 每个元素都与以下位置的对应元素逐对比较：
     * 另一个向量中相同索引处的元素；例如，先检查以下值：
     * 索引依次为 0、1，依此类推。
     * <、>、<=、>= 运算符要求 ValueType 定义 < 运算符
     * 以便逐对比较各元素。
     * @bigoh O(N)
     */
    bool operator <=(const Vector& v2) const;

    /**
     * 用于比较两个向量的关系运算符。
     * 每个元素都与以下位置的对应元素逐对比较：
     * 另一个向量中相同索引处的元素；例如，先检查以下值：
     * 索引依次为 0、1，依此类推。
     * <、>、<=、>= 运算符要求 ValueType 定义 < 运算符
     * 以便逐对比较各元素。
     * @bigoh O(N)
     */
    bool operator >(const Vector& v2) const;

    /**
     * 用于比较两个向量的关系运算符。
     * 每个元素都与以下位置的对应元素逐对比较：
     * 另一个向量中相同索引处的元素；例如，先检查以下值：
     * 索引依次为 0、1，依此类推。
     * <、>、<=、>= 运算符要求 ValueType 定义 < 运算符
     * 以便逐对比较各元素。
     * @bigoh O(N)
     */
    bool operator >=(const Vector& v2) const;

    /*
     * 其他 Vector 操作
     * ----------------------------
     * 除本接口中列出的方法外，Vector
     * 类支持以下操作：
     *
     *   - 使用 << 和 >> 运算符进行流输入/输出
     *   - 为复制构造函数和赋值运算符实现深拷贝
     *   - 使用基于范围的 for 语句或 STL 迭代器进行迭代
     *
     * 这些迭代形式按索引顺序处理 Vector。
     */

    /* 私有部分 */

    /**********************************************************************/
    /* 注意：文件中此处以下的所有内容在逻辑上都属于    */
    /* 属于实现细节，客户端无需关注。    */
    /**********************************************************************/

private:
    /*
     * 实现说明：Vector 数据结构
     * -------------------------------------------
     * 元素存储在 std::vector 中，即标准 C++ 库
     * 表示元素序列的类型。我们包装 std::vector 是因为
     * 它没有运行时安全检查，这一点需要时间适应
     * 适用于你刚开始学习使用这些类型时。
     *
     * C++ 库中有一个边界情况：std::vector<bool> 不会
     * 并不像你可能认为的那样工作。这被广泛认为是一个错误
     * 这是语言设计中的问题，多年来一直有修复它的提案
     * 已经很多年。在此期间，我们通过回退到
     * 当客户端希望创建以下对象时使用 std::deque 类型
     * Vector<bool>
     */
    using ContainerType = typename std::conditional<std::is_same<ValueType, bool>::value,
                                                    std::deque<bool>,
                                                    std::vector<ValueType>>::type;

    /* 实例变量 */
    ContainerType _elements;
    stanfordcpplib::collections::VersionTracker _version;

    /* 私有方法 */

    /*
     * 如果给定索引不在以下范围内，则抛出 ErrorException：
     * [min..max]，包含两端。
     * 这是供 Vector 各成员使用的统一错误处理程序，这些成员
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
    /**
     * 将元素添加到作为左操作数传入的向量。
     * 此形式使在旧版 C++ 中初始化 Vector 更方便。
     * @bigoh O(1)
     */
    Vector& operator ,(const ValueType& value);

    using iterator = stanfordcpplib::collections::CheckedIterator<typename ContainerType::iterator>;
    using const_iterator = stanfordcpplib::collections::CheckedIterator<typename ContainerType::const_iterator>;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    /* 更新内部版本计数。只有我们的库需要此功能，并且它们仅
     * 在少数情况下需要它：某操作语义上会修改，但按位来看
     * 发生非修改操作。
     */
    void updateVersion();
};

/* 实现部分 */

template <typename ValueType>
Vector<ValueType>::Vector(int n, ValueType value) {
    if (n < 0) error("Cannot create a Vector with a negative number of elements.");
    _elements.assign(n, value);
}

template <typename ValueType>
Vector<ValueType>::Vector(std::initializer_list<ValueType> list)
        : _elements(list) {
}

/*
 * 实现说明：Vector 方法
 * ------------------------------------
 * 基本 Vector 方法很直接，应只需要
 * 没有详细文档。
 */
template <typename ValueType>
void Vector<ValueType>::add(const ValueType& value) {
    insert(size(), value);
}

template <typename ValueType>
Vector<ValueType>& Vector<ValueType>::addAll(const Vector<ValueType>& v) {
    for (const ValueType& value : v) {
        add(value);
    }
    return *this;   // 错误修复 2014/04/27
}

template <typename ValueType>
void Vector<ValueType>::clear() {
    _elements.clear();
    _version.update();
}

template <typename ValueType>
bool Vector<ValueType>::equals(const Vector<ValueType>& v) const {
    return stanfordcpplib::collections::equals(*this, v);
}

template <typename ValueType>
const ValueType& Vector<ValueType>::get(int index) const {
    checkIndex(index, 0, size()-1, "get");
    return _elements[index];
}

template <typename ValueType>
void Vector<ValueType>::insert(int index, const ValueType& value) {
    checkIndex(index, 0, size(), "insert");
    _elements.insert(_elements.begin() + index, value);
    _version.update();
}

template <typename ValueType>
bool Vector<ValueType>::isEmpty() const {
    return _elements.empty();
}

/*
 * 实现说明：mapAll
 * ----------------------------
 * mapAll 函数的各种版本会应用该函数或
 * 按索引升序对每个元素调用函数对象。
 */
template <typename ValueType>
void Vector<ValueType>::mapAll(std::function<void (const ValueType&)> fn) const {
    for (const auto& elem: _elements) {
        fn(elem);
    }
}

template <typename ValueType>
ValueType Vector<ValueType>::remove(int index) {
    checkIndex(index, 0, size() - 1, "remove");
    ValueType elem = _elements[index];
    _elements.erase(_elements.begin() + index);
    _version.update();
    return elem;
}

template <typename ValueType>
void Vector<ValueType>::set(int index, const ValueType& value) {
    checkIndex(index, 0, size()-1, "set");
    _elements[index] = value;
}

template <typename ValueType>
int Vector<ValueType>::size() const {
    return _elements.size();
}

template <typename ValueType>
void Vector<ValueType>::sort() {
    std::sort(begin(), end());
}

template <typename ValueType>
Vector<ValueType> Vector<ValueType>::subList(int start, int length) const {
    checkIndex(start, 0, size(), "subList");
    checkIndex(start + length, 0, size(), "subList");
    if (length < 0) {
        error("Vector::subList: length cannot be negative");
    }
    Vector<ValueType> result;
    for (int i = start; i < start + length; i++) {
        result.add(get(i));
    }
    return result;
}

template <typename ValueType>
Vector<ValueType> Vector<ValueType>::subList(int start) const {
    return subList(start, size() - start);
}

template <typename ValueType>
std::string Vector<ValueType>::toString() const {
    std::ostringstream os;
    os << *this;
    return os.str();
}

/*
 * 实现说明：Vector 选择
 * --------------------------------------
 * 以下代码使用以下方式实现传统数组选择：
 * 用于索引的方括号。
 */
template <typename ValueType>
ValueType& Vector<ValueType>::operator [](int index) {
    return const_cast<ValueType&>(static_cast<const Vector &>(*this)[index]);
}
template <typename ValueType>
const ValueType& Vector<ValueType>::operator [](int index) const {
    checkIndex(index, 0, size()-1, "operator []");
    return _elements[index];
}

template <typename ValueType>
Vector<ValueType> Vector<ValueType>::operator +(const Vector& v2) const {
    Vector<ValueType> result = *this;
    return result.addAll(v2);
}

template <typename ValueType>
Vector<ValueType> Vector<ValueType>::operator +(const ValueType& elem) const {
    Vector<ValueType> result = *this;
    return result += elem;
}

template <typename ValueType>
Vector<ValueType>& Vector<ValueType>::operator +=(const Vector& v2) {
    return addAll(v2);
}

template <typename ValueType>
Vector<ValueType>& Vector<ValueType>::operator +=(const ValueType& value) {
    add(value);
    return *this;
}

template <typename ValueType>
bool Vector<ValueType>::operator ==(const Vector& v2) const {
    return equals(v2);
}

template <typename ValueType>
bool Vector<ValueType>::operator !=(const Vector& v2) const {
    return !equals(v2);
}

template <typename ValueType>
bool Vector<ValueType>::operator <(const Vector& v2) const {
    return stanfordcpplib::collections::compare(*this, v2) < 0;
}

template <typename ValueType>
bool Vector<ValueType>::operator <=(const Vector& v2) const {
    return stanfordcpplib::collections::compare(*this, v2) <= 0;
}

template <typename ValueType>
bool Vector<ValueType>::operator >(const Vector& v2) const {
    return stanfordcpplib::collections::compare(*this, v2) > 0;
}

template <typename ValueType>
bool Vector<ValueType>::operator >=(const Vector& v2) const {
    return stanfordcpplib::collections::compare(*this, v2) >= 0;
}

template <typename ValueType>
void Vector<ValueType>::checkIndex(int index, int min, int max, const char* prefix) const {
    if (index < min || index > max) {
        std::ostringstream out;
        out << "Vector::" << prefix << ": index of " << index
            << " is outside of valid range ";
        if (isEmpty()) {
            out << " (empty vector)";
        } else {
            out << "[";
            if (min < max) {
                out << min << ".." << max;
            } else if (min == max) {
                out << min;
            } // 否则 min > max，没有范围，空向量
            out << "]";
        }
        error(out.str());
    }
}

/*
 * 实现说明：逗号运算符
 * ------------------------------------
 * 逗号运算符通过将右操作数添加到 vector 来工作，并
 * 然后按引用返回 Vector，以便为下一次
 * 链中的值。
 */
template <typename ValueType>
Vector<ValueType>& Vector<ValueType>::operator ,(const ValueType& value) {
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
std::ostream& operator <<(std::ostream& os, const Vector<ValueType>& vec) {
    return stanfordcpplib::collections::writeCollection(os, vec);
}

template <typename ValueType>
std::istream& operator >>(std::istream& is, Vector<ValueType>& vec) {
    ValueType element;
    return stanfordcpplib::collections::readCollection(is, vec, element, /* 描述符 */ "Vector::operator >>");
}


/*
 * 实现说明：迭代器支持
 * --------------------------------------
 * 我们使用了已检查的迭代器类型，这要求提供
 * 关于可用值的完整范围。
 */
template <typename ValueType>
typename Vector<ValueType>::iterator Vector<ValueType>::begin() {
    return { &_version, _elements.begin(), _elements };
}
template <typename ValueType>
typename Vector<ValueType>::const_iterator Vector<ValueType>::begin() const {
    return { &_version, _elements.begin(), _elements };
}
template <typename ValueType>
typename Vector<ValueType>::iterator Vector<ValueType>::end() {
    return { &_version, _elements.end(), _elements };
}
template <typename ValueType>
typename Vector<ValueType>::const_iterator Vector<ValueType>::end() const {
    return { &_version, _elements.end(), _elements };
}

template <typename ValueType>
void Vector<ValueType>::updateVersion() {
    _version.update();
}

/*
 * 向量的模板哈希函数。
 * 要求 Vector 中的元素类型具有 hashCode 函数。
 */
template <typename ValueType>
int hashCode(const Vector<ValueType>& vec) {
    return stanfordcpplib::collections::hashCodeCollection(vec);
}

/*
 * 函数：randomElement
 * 用法：element = randomElement(v);
 * ----------------------------------
 * 返回从给定向量中随机选择的元素。
 * 如果 Vector 为空，则抛出错误。
 */
template <typename T>
const T& randomElement(const Vector<T>& vec) {
    return stanfordcpplib::collections::randomElementIndexed(vec);
}


#endif // _vector_h
