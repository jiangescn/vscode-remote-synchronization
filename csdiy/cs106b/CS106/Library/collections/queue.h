/*
 * 文件：queue.h
 * -------------
 * 此文件导出 <code>Queue</code> 类，它是一种集合
 * 其中值通常按先进先出顺序处理
 * （FIFO，先进先出）顺序。
 */

#ifndef _queue_h
#define _queue_h

#include <initializer_list>

#include "collections.h"
#include "deque.h"
#include "error.h"
#include "hashcode.h"
#include "vector.h"

/*
 * 类：Queue<ValueType>
 * -----------------------
 * 此类对一种称为<b><i>队列</i></b>的线性结构建模
 * 其中值从一端添加、从另一端移除。
 * 这种规则产生先进先出（FIFO）的行为
 * 这是队列的定义性特征。
 */
template <typename ValueType>
class Queue {
public:
    /*
     * 构造函数：Queue
     * 用法：Queue<ValueType> queue;
     * ------------------------------
     * 初始化一个新的空队列。
     */
    Queue() = default;

    /*
     * 构造函数：Queue
     * 用法：Queue<ValueType> queue {1, 2, 3};
     * ----------------------------------------
     * 初始化一个按从前到后顺序存储给定元素的新队列。
     */
    Queue(std::initializer_list<ValueType> list);

    /*
     * 析构函数：~Queue
     * ------------------
     * 释放与此队列关联的任何堆存储。
     */
    virtual ~Queue() = default;

    /*
     * 方法：clear
     * 用法：queue.clear();
     * ---------------------
     * 从队列中删除所有元素。
     */
    void clear();

    /*
     * 方法：dequeue
     * 用法：ValueType first = queue.dequeue();
     * -----------------------------------------
     * 删除并返回队列中的第一项。
     */
    ValueType dequeue();

    /*
     * 方法：enqueue
     * 用法：queue.enqueue(value);
     * ----------------------------
     * 将 <code>value</code> 添加到队列末尾。
     */
    void enqueue(const ValueType& value);

    /*
     * 方法：equals
     * 用法：if (queue.equals(queue2)) ...
     * ------------------------------------
     * 比较两个队列是否相等。
     * 如果此队列包含完全相同的内容，则返回 <code>true</code>
     * 与给定另一个队列相同的值。
     * 行为与 == 运算符相同。
     */
    bool equals(const Queue<ValueType>& queue2) const;

    /*
     * 方法：isEmpty
     * 用法：if (queue.isEmpty()) ...
     * -------------------------------
     * 如果队列不包含元素，则返回 <code>true</code>。
     */
    bool isEmpty() const;

    /*
     * 方法：peek
     * 用法：ValueType first = queue.peek();
     * --------------------------------------
     * 返回队列中的第一个值，但不移除它。
     */
    const ValueType& peek() const;

    /*
     * 方法：size
     * 用法：int n = queue.size();
     * ----------------------------
     * 返回队列中的值数量。
     */
    int size() const;

    /*
     * 方法：toString
     * 用法：string str = queue.toString();
     * -------------------------------------
     * 将队列转换为可打印的字符串表示。
     */
    std::string toString() const;

    /*
     * 运算符：==
     * 用法：queue1 == queue2
     * -------------------
     * 如果 <code>queue1</code> 和 <code>queue2</code>，则返回 <code>true</code>
     * 包含相同元素。
     */
    bool operator ==(const Queue& queue2) const;

    /*
     * 运算符：!=
     * 用法：queue1 != queue2
     * -------------------
     * 如果 <code>queue1</code> 和 <code>queue2</code>，则返回 <code>true</code>
     * 不包含相同元素。
     */
    bool operator !=(const Queue& queue2) const;

    /*
     * 运算符：<、>、<=、>=
     * 用法：queue1 < queue2 ...
     * --------------------------
     * 用于比较两个队列的关系运算符。
     * <、>、<=、>= 运算符要求 ValueType 定义 < 运算符
     * 以便逐对比较各元素。
     */
    bool operator <(const Queue& queue2) const;
    bool operator <=(const Queue& queue2) const;
    bool operator >(const Queue& queue2) const;
    bool operator >=(const Queue& queue2) const;

    template <typename T>
    friend int hashCode(const Queue<T>& s);

    template <typename T>
    friend std::ostream& operator <<(std::ostream& os, const Queue<T>& queue);

    /* 私有部分 */

    /**********************************************************************/
    /* 注意：文件中此处以下的所有内容在逻辑上都属于    */
    /* 属于实现细节，客户端无需关注。    */
    /**********************************************************************/

private:
    /* 实例变量 */
    Deque<ValueType> _elements;
};

template <typename ValueType>
Queue<ValueType>::Queue(std::initializer_list<ValueType> list) : _elements(list) {
    // 空
}

template <typename ValueType>
void Queue<ValueType>::clear() {
    _elements.clear();
}

/*
 * 实现说明：dequeue、peek
 * -----------------------------------
 * 这些方法必须检查空队列，并报告错误
 * 若不存在第一个元素。
 */
template <typename ValueType>
ValueType Queue<ValueType>::dequeue() {
    if (isEmpty()) {
        error("Queue::dequeue: Attempting to dequeue an empty queue");
    }
    return _elements.dequeueFront();
}

template <typename ValueType>
void Queue<ValueType>::enqueue(const ValueType& value) {
    _elements.enqueueBack(value);
}

template <typename ValueType>
bool Queue<ValueType>::equals(const Queue<ValueType>& queue2) const {
    return *this == queue2;
}

template <typename ValueType>
bool Queue<ValueType>::isEmpty() const {
    return _elements.isEmpty();
}

template <typename ValueType>
const ValueType& Queue<ValueType>::peek() const {
    if (isEmpty()) {
        error("Queue::peek: Attempting to peek at an empty queue");
    }
    return _elements.peekFront();
}

template <typename ValueType>
int Queue<ValueType>::size() const {
    return _elements.size();
}

template <typename ValueType>
std::string Queue<ValueType>::toString() const {
    std::ostringstream os;
    os << *this;
    return os.str();
}

template <typename ValueType>
bool Queue<ValueType>::operator ==(const Queue& queue2) const {
    return _elements == queue2._elements;
}

template <typename ValueType>
bool Queue<ValueType>::operator !=(const Queue& queue2) const {
    return _elements != queue2._elements;
}

template <typename ValueType>
bool Queue<ValueType>::operator <(const Queue& queue2) const {
    return _elements < queue2._elements;
}

template <typename ValueType>
bool Queue<ValueType>::operator <=(const Queue& queue2) const {
    return _elements <= queue2._elements;
}

template <typename ValueType>
bool Queue<ValueType>::operator >(const Queue& queue2) const {
    return _elements > queue2._elements;
}

template <typename ValueType>
bool Queue<ValueType>::operator >=(const Queue& queue2) const {
    return _elements >= queue2._elements;
}

template <typename ValueType>
std::ostream& operator <<(std::ostream& os, const Queue<ValueType>& queue) {
    return os << queue._elements;
}

template <typename ValueType>
    void readOne(Queue<ValueType>& queue, const ValueType& value)
        { queue.enqueue(value); }

template <typename ValueType>
std::istream& operator >>(std::istream& is, Queue<ValueType>& queue) {
    ValueType element;
    return stanfordcpplib::collections::readCollection(is, queue, element, /* 描述符 */ "Queue::operator >>", readOne<ValueType>);
}


/*
 * 队列的模板哈希函数。
 * 要求队列中的元素类型具有 hashCode 函数。
 */
template <typename T>
int hashCode(const Queue<T>& q) {
    return hashCode(q._elements);
}

#endif // _queue_h
