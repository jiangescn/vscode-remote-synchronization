/*
 * 文件：deque.h
 * -------------
 * 此文件导出 <code>Deque</code> 类，它是一种集合
 * 其中值可以从前端或后端添加和移除。
 * 它结合了栈和队列的大部分功能。
 */

#ifndef _deque_h
#define _deque_h

#include <deque>
#include <initializer_list>

#include "collections.h"
#include "error.h"
#include "hashcode.h"

/*
 * 类：Deque<ValueType>
 * -----------------------
 * 此类对一种称为<b><i>双端队列</i></b>的线性结构建模
 * 其中值可在任一端添加和移除。
 * 这种规则允许先进先出（FIFO）和/或
 * 后进先出（LIFO）行为。这是其定义性
 * 双端队列的特性。
 */
template <typename ValueType>
class Deque {
public:
    /*
     * 构造函数：Deque
     * 用法：Deque<ValueType> deque;
     * ------------------------------
     * 初始化一个新的空双端队列。
     */
    Deque() = default;

    /*
     * 构造函数：Deque
     * 用法：Deque<ValueType> queue {1, 2, 3};
     * ----------------------------------------
     * 初始化一个按从前到后顺序存储给定元素的新双端队列。
     */
    Deque(std::initializer_list<ValueType> list);

    /*
     * 析构函数：~Deque
     * ------------------
     * 释放与此双端队列关联的任何堆存储。
     */
    virtual ~Deque() = default;

    /*
     * 方法：clear
     * 用法：deque.clear();
     * ---------------------
     * 从双端队列中删除所有元素。
     */
    void clear();

    /*
     * 方法：dequeueBack、dequeueFront
     * 用法：ValueType first = deque.dequeueFront();
     * ----------------------------------------------
     * 删除并返回双端队列最前端/最后端的项目。
     */
    ValueType dequeueBack();
    ValueType dequeueFront();

    /*
     * 方法：enqueueBack、enqueueFront
     * 用法：deque.enqueueBack(value);
     * --------------------------------
     * 将 <code>value</code> 添加到双端队列的前端/后端。
     */
    void enqueueBack(const ValueType& value);
    void enqueueFront(const ValueType& value);

    /*
     * 方法：equals
     * 用法：if (deque.equals(deque2)) ...
     * ------------------------------------
     * 比较两个双端队列是否相等。
     * 如果此双端队列包含完全相同的内容，则返回 <code>true</code>
     * 与给定另一个双端队列相同的值。
     * 行为与 == 运算符相同。
     */
    bool equals(const Deque<ValueType>& deque2) const;

    /*
     * 方法：isEmpty
     * 用法：if (deque.isEmpty()) ...
     * -------------------------------
     * 如果双端队列不包含元素，则返回 <code>true</code>。
     */
    bool isEmpty() const;

    /*
     * 方法：peekBack、peekFront
     * 用法：ValueType first = deque.peekFront();
     * -------------------------------------------
     * 返回双端队列最前端/最后端的值，但不移除它。
     */
    const ValueType& peekBack() const;
    const ValueType& peekFront() const;

    /*
     * 方法：size
     * 用法：int n = deque.size();
     * ----------------------------
     * 返回双端队列中的值数量。
     */
    int size() const;

    /*
     * 方法：toString
     * 用法：string str = deque.toString();
     * -------------------------------------
     * 将双端队列转换为可打印的字符串表示。
     */
    std::string toString() const;

    /*
     * 运算符：==、!=、<、>、<=、>=
     * 用法：if (deque1 == deque2) ...
     * 用法：if (deque1 < deque2) ...
     * ...
     * --------------------------------
     * 用于比较两个双端队列的关系运算符。
     * ==、!= 运算符要求 ValueType 定义 == 运算符
     * 以便测试元素是否相等。
     * <、>、<=、>= 运算符要求 ValueType 定义 < 运算符
     * 以便逐对比较各元素。
     */
    bool operator ==(const Deque& deque2) const;
    bool operator !=(const Deque& deque2) const;
    bool operator <(const Deque& deque2) const;
    bool operator <=(const Deque& deque2) const;
    bool operator >(const Deque& deque2) const;
    bool operator >=(const Deque& deque2) const;

    /* 私有部分 */

    /**********************************************************************/
    /* 注意：文件中此处以下的所有内容在逻辑上都属于    */
    /* 属于实现细节，客户端无需关注。    */
    /**********************************************************************/

    template <typename T>
    friend int hashCode(const Deque<T>& s);

    template <typename T>
    friend std::ostream& operator <<(std::ostream& os, const Deque<T>& deque);

private:
    // 实例变量
    std::deque<ValueType> _elements;
    stanfordcpplib::collections::VersionTracker _version;

public:

    using iterator = stanfordcpplib::collections::CheckedIterator<typename std::deque<ValueType>::iterator>;
    using const_iterator = stanfordcpplib::collections::CheckedIterator<typename std::deque<ValueType>::const_iterator>;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
};

template <typename ValueType>
Deque<ValueType>::Deque(std::initializer_list<ValueType> list) : _elements(list) {

}
template <typename ValueType>
void Deque<ValueType>::clear() {
    _elements.clear();
    _version.update();
}

/*
 * 实现说明：dequeue、peek
 * -----------------------------------
 * 这些方法必须检查双端队列是否为空，并报告错误
 * 若不存在第一个元素。
 */

template <typename ValueType>
ValueType Deque<ValueType>::dequeueBack() {
    if (isEmpty()) {
        error("Deque::dequeueBack: Attempting to dequeue from an empty deque");
    }
    auto result = _elements.back();
    _elements.pop_back();
    _version.update();
    return result;
}

template <typename ValueType>
ValueType Deque<ValueType>::dequeueFront() {
    if (isEmpty()) {
        error("Deque::dequeueFront: Attempting to dequeue from an empty deque");
    }
    auto result = _elements.front();
    _elements.pop_front();
    _version.update();
    return result;
}

template <typename ValueType>
void Deque<ValueType>::enqueueBack(const ValueType& value) {
    _elements.push_back(value);
    _version.update();
}

template <typename ValueType>
void Deque<ValueType>::enqueueFront(const ValueType& value) {
    _elements.push_front(value);
    _version.update();
}

template <typename ValueType>
bool Deque<ValueType>::equals(const Deque<ValueType>& deque2) const {
    return _elements == deque2._elements;
}

template <typename ValueType>
bool Deque<ValueType>::isEmpty() const {
    return _elements.empty();
}

template <typename ValueType>
const ValueType& Deque<ValueType>::peekBack() const {
    if (isEmpty()) {
        error("Deque::peekBack: Attempting to peek at an empty deque");
    }
    return _elements.back();
}

template <typename ValueType>
const ValueType& Deque<ValueType>::peekFront() const {
    if (isEmpty()) {
        error("Deque::peekFront: Attempting to peek at an empty deque");
    }
    return _elements.front();
}

template <typename ValueType>
int Deque<ValueType>::size() const {
    return _elements.size();
}

template <typename ValueType>
std::string Deque<ValueType>::toString() const {
    std::ostringstream os;
    os << *this;
    return os.str();
}

template <typename ValueType>
bool Deque<ValueType>::operator ==(const Deque& deque2) const {
    return equals(deque2);
}

template <typename ValueType>
bool Deque<ValueType>::operator !=(const Deque& deque2) const {
    return !equals(deque2);
}

template <typename ValueType>
bool Deque<ValueType>::operator <(const Deque& deque2) const {
    return stanfordcpplib::collections::compare(_elements, deque2._elements) < 0;
}

template <typename ValueType>
bool Deque<ValueType>::operator <=(const Deque& deque2) const {
    return stanfordcpplib::collections::compare(_elements, deque2._elements) <= 0;
}

template <typename ValueType>
bool Deque<ValueType>::operator >(const Deque& deque2) const {
    return stanfordcpplib::collections::compare(_elements, deque2._elements) > 0;
}

template <typename ValueType>
bool Deque<ValueType>::operator >=(const Deque& deque2) const {
    return stanfordcpplib::collections::compare(_elements, deque2._elements) >= 0;
}

template <typename ValueType>
std::ostream& operator <<(std::ostream& os, const Deque<ValueType>& deque) {
    return stanfordcpplib::collections::writeCollection(os, deque);
}

template <typename ValueType>
    void readOne(Deque<ValueType>& deque, const ValueType& value)
        { deque.enqueueBack(value); }

template <typename ValueType>
std::istream& operator >>(std::istream& is, Deque<ValueType>& deque) {
    ValueType element;
    return stanfordcpplib::collections::readCollection(is, deque, element, /* 描述符 */ "Deque::operator >>", readOne<ValueType>);
}

template <typename ValueType>
typename Deque<ValueType>::iterator Deque<ValueType>::begin() {
    return { &_version, _elements.begin(), _elements };
}
template <typename ValueType>
typename Deque<ValueType>::const_iterator Deque<ValueType>::begin() const {
    return { &_version, _elements.begin(), _elements };
}

template <typename ValueType>
typename Deque<ValueType>::iterator Deque<ValueType>::end() {
    return { &_version, _elements.end(), _elements };
}
template <typename ValueType>
typename Deque<ValueType>::const_iterator Deque<ValueType>::end() const {
    return { &_version, _elements.end(), _elements };
}

/*
 * 双端队列的模板哈希函数。
 * 要求双端队列中的元素类型具有 hashCode 函数。
 */
template <typename T>
int hashCode(const Deque<T>& deq) {
    return stanfordcpplib::collections::hashCodeCollection(deq);
}

#endif // _deque_h
