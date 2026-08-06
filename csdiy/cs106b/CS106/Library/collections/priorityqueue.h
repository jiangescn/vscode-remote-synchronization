/*
 * 文件：priorityqueue.h
 * ---------------------
 * 此文件导出 <code>PriorityQueue</code> 类，它是一种
 * 按优先级顺序处理值的集合。
 */

#ifndef _priorityqueue_h
#define _priorityqueue_h

#include <cmath>
#include <initializer_list>
#include <utility>
#include <queue>
#include <algorithm>

#include "collections.h"
#include "error.h"
#include "gmath.h"
#include "hashcode.h"
#include "vector.h"

/*
 * 类：PriorityQueue<ValueType>
 * -------------------------------
 * 此类对一种称为<b><i>优先队列</i></b>的结构建模
 * 其中值按优先级顺序处理。与传统方式一样
 * 按照英语惯例，较小的优先级数值表示更高的实际
 * 优先级，因此优先级为 1 的项目优先于
 * 优先级为 2 的项目。
 */

template <typename ValueType>
class PriorityQueue {
public:
    /*
     * 构造函数：PriorityQueue
     * 用法：PriorityQueue<ValueType> pq;
     * -----------------------------------
     * 初始化一个新的优先队列，其初始为空。
     */
    PriorityQueue() = default;

    /*
     * 构造函数：PriorityQueue
     * 用法：PriorityQueue<ValueType> pq {{1.0, "a"}, {2.0, "b"}, {3.0, "c"}};
     * -------------------------------------------------------------------------
     * 初始化一个存储给定键值对的新优先队列。
     * 请注意，键值对按优先级顺序存储，而不是
     * 不一定与它们在初始化列表中的书写顺序相同。
     */
    PriorityQueue(std::initializer_list<std::pair<double, ValueType>> list);

    /*
     * 析构函数：~PriorityQueue
     * --------------------------
     * 释放与此优先队列关联的任何堆存储。
     */
    virtual ~PriorityQueue() = default;

    /*
     * 方法：changePriority
     * 用法：pq.changePriority(value, newPriority);
     * ---------------------------------------------
     * 调整队列中的 <code>value</code>，使其具有指定的新优先级，
     * 其紧急程度必须至少与该值此前的优先级相同（数字更小）
     * 队列中的优先级。
     * 如果队列中不存在该元素值，或者
     * 传入的新优先级不至少与当前优先级同样紧急。
     */
    void changePriority(ValueType value, double newPriority);

    /*
     * 方法：clear
     * 用法：pq.clear();
     * ------------------
     * 从优先队列中删除所有元素。
     */
    void clear();

    /*
     * 方法：dequeue
     * 用法：ValueType first = pq.dequeue();
     * --------------------------------------
     * 删除并返回最高优先级的值。如果有多个
     * 队列中具有相同优先级的条目会
     * 按入队时的相同顺序出队。
     */
    ValueType dequeue();

    /*
     * 方法：enqueue
     * 用法：pq.enqueue(value, priority);
     * -----------------------------------
     * 以指定优先级将 <code>value</code> 添加到队列。
     * 较小的优先级数字对应更高的优先级，这
     * 表示所有优先级为 1 的元素都会在任何其他元素之前出队
     * 优先级为 2 的元素。
     */
    void enqueue(const ValueType& value, double priority);

    /*
     * 方法：equals
     * 用法：if (pq.equals(pq2)) ...
     * ------------------------------
     * 比较两个优先队列是否相等。
     * 如果此队列包含完全相同的内容，则返回 <code>true</code>
     * 与给定另一个队列相同的值和优先级。
     * 行为与 == 运算符相同。
     */
    bool equals(const PriorityQueue<ValueType>& pq2) const;

    /*
     * 方法：isEmpty
     * 用法：if (pq.isEmpty()) ...
     * ----------------------------
     * 如果优先队列不包含元素，则返回 <code>true</code>。
     */
    bool isEmpty() const;

    /*
     * 方法：peek
     * 用法：ValueType first = pq.peek();
     * -----------------------------------
     * 返回队列中优先级最高的值，但不
     * 将其移除。
     */
    const ValueType& peek() const;

    /*
     * 方法：peekPriority
     * 用法：double priority = pq.peekPriority();
     * -------------------------------------------
     * 返回队列中第一个元素的优先级，但不
     * 将其移除。
     */
    double peekPriority() const;

    /*
     * 方法：size
     * 用法：int n = pq.size();
     * -------------------------
     * 返回优先队列中的值数量。
     */
    int size() const;

    /*
     * 方法：toString
     * 用法：string str = pq.toString();
     * ----------------------------------
     * 将队列转换为可打印的字符串表示。
     */
    std::string toString() const;

    /*
     * 运算符：<<
     * 将优先队列打印到给定输出流。
     */
    template <typename T>
    friend std::ostream& operator <<(std::ostream& os, const PriorityQueue<T>& pq);

    /*
     * 运算符：==、!=
     * 用法：if (pq1 == pq2) ...
     * --------------------------
     * 用于比较两个队列是否包含相同元素的关系运算符。
     * ==、!= 运算符要求 ValueType 定义 == 运算符
     * 以便测试元素是否相等。
     */
    bool operator ==(const PriorityQueue& pq2) const;
    bool operator !=(const PriorityQueue& pq2) const;

    /* 私有部分 */

    /**********************************************************************/
    /* 注意：文件中此处以下的所有内容在逻辑上都属于    */
    /* 属于实现细节，客户端无需关注。    */
    /**********************************************************************/

    /*
     * 实现说明：PriorityQueue 数据结构
     * --------------------------------------------------
     * PriorityQueue 类使用一种称为
     * 一个堆。
     */
private:
    /* 用于每个堆条目的类型 */
    struct HeapEntry {
        ValueType value;
        double priority;
        long sequence;

        bool operator < (const HeapEntry& rhs) const;
    };

    /* 实例变量 */
    Vector<HeapEntry> _heap;
    long _enqueueCount = 0;

public:
    /* 私有实现部分 */

    template <typename Collection>
    friend int stanfordcpplib::collections::compare(const Collection& pq1, const Collection& pq2);

};

template <typename ValueType>
PriorityQueue<ValueType>::PriorityQueue(
        std::initializer_list<std::pair<double, ValueType>> list) {
    for (std::pair<double, ValueType> pair : list) {
        enqueue(pair.second, pair.first);
    }
}

/*
 * Marty Stepp 添加了 changePriority 函数。
 * 此实现的部分内容改编自 TrailblazerPQueue.h，
 * 由 Keith Schwarz 编写。
 */
template <typename ValueType>
void PriorityQueue<ValueType>::changePriority(ValueType value, double newPriority) {
    if (std::isnan(newPriority)) {
        error("PriorityQueue::changePriority: Attempted to use NaN as a priority.");
    }
    if (floatingPointEqual(newPriority, -0.0)) {
        newPriority = 0.0;
    }

    /* 找到要更改的元素。 */
    auto itr = std::find_if(_heap.begin(), _heap.end(), [&](const HeapEntry& entry) {
        return entry.value == value;
    });
    if (itr == _heap.end()) {
        error("PriorityQueue::changePriority: Element not found in priority queue.");
    }

    if (itr->priority < newPriority) {
        error("PriorityQueue::changePriority: new priority cannot be less urgent than current priority.");
    }
    itr->priority = newPriority;
    std::push_heap(_heap.begin(), itr + 1);
}

template <typename ValueType>
void PriorityQueue<ValueType>::clear() {
    _heap.clear();
    _enqueueCount = 0;   // BUG 修复 2014/10/10：之前使用了未赋值的垃圾值
}

/*
 * 实现说明：dequeue、peek、peekPriority
 * -------------------------------------------------
 * 这些方法必须检查空队列，并报告错误
 * 若不存在第一个元素。
 */
template <typename ValueType>
ValueType PriorityQueue<ValueType>::dequeue() {
    if (isEmpty()) {
        error("PriorityQueue::dequeue: Attempting to dequeue an empty queue");
    }

    ValueType result = _heap[0].value;
    std::pop_heap(_heap.begin(), _heap.end());
    _heap.remove(_heap.size() - 1);
    return result;
}

template <typename ValueType>
void PriorityQueue<ValueType>::enqueue(const ValueType& value, double priority) {
    if (std::isnan(priority)) {
        error("PriorityQueue::enqueue: Attempted to use NaN as a priority.");
    }
    if (floatingPointEqual(priority, -0.0)) {
        priority = 0.0;
    }

    _heap.add({ value, priority, _enqueueCount++ });
    std::push_heap(_heap.begin(), _heap.end());
}

template <typename ValueType>
bool PriorityQueue<ValueType>::equals(const PriorityQueue<ValueType>& pq2) const {
    // 优化：如果确实是同一优先队列，则停止
    if (this == &pq2) {
        return true;
    }
    if (size() != pq2.size()) {
        return false;
    }
    PriorityQueue<ValueType> backup1 = *this;
    PriorityQueue<ValueType> backup2 = pq2;
    while (!backup1.isEmpty() && !backup2.isEmpty()) {
        if (!floatingPointEqual(backup1.peekPriority(), backup2.peekPriority())) {
            return false;
        }
        if (backup1.dequeue() != backup2.dequeue()) {
            return false;
        }
    }
    return backup1.isEmpty() == backup2.isEmpty();
}

template <typename ValueType>
bool PriorityQueue<ValueType>::isEmpty() const {
    return _heap.size() == 0;
}

template <typename ValueType>
const ValueType& PriorityQueue<ValueType>::peek() const {
    if (isEmpty()) {
        error("PriorityQueue::peek: Attempting to peek at an empty queue");
    }
    return _heap[0].value;
}

template <typename ValueType>
double PriorityQueue<ValueType>::peekPriority() const {
    if (isEmpty()) {
        error("PriorityQueue::peekPriority: Attempting to peek at an empty queue");
    }
    return _heap[0].priority;
}

template <typename ValueType>
int PriorityQueue<ValueType>::size() const {
    return _heap.size();
}

template <typename ValueType>
std::string PriorityQueue<ValueType>::toString() const {
    std::ostringstream os;
    os << *this;
    return os.str();
}


/*
 * 堆条目的比较函数。比较按字典序进行，首先按
 * 先按优先级，再按序列号。
 *
 * 因为 std::push_heap 和 std::pop_heap 尝试创建最大堆，而我们希望
 * 在最小堆中，优先级比较方向相反。
 */
template <typename ValueType>
bool PriorityQueue<ValueType>::HeapEntry::operator < (const HeapEntry& rhs) const {
    if (priority > rhs.priority) return true;
    if (rhs.priority > priority) return false;

    return sequence < rhs.sequence;
}

template <typename ValueType>
bool PriorityQueue<ValueType>::operator ==(const PriorityQueue& pq2) const {
    return equals(pq2);
}

template <typename ValueType>
bool PriorityQueue<ValueType>::operator !=(const PriorityQueue& pq2) const {
    return !equals(pq2);
}

/*
 * 优先队列的模板哈希函数。
 * 要求优先队列中的元素类型具有 hashCode 函数。
 */
template <typename T>
int hashCode(const PriorityQueue<T>& pq) {
    // （缓慢且内存效率低的实现）：复制 pq，将所有元素出队，再组合哈希
    PriorityQueue<T> backup = pq;
    int code = hashSeed();
    while (!backup.isEmpty()) {
        code = hashMultiplier() * code + hashCode(backup.peek());
        code = hashMultiplier() * code + hashCode(backup.peekPriority());
        backup.dequeue();
    }
    return int(code & hashMask());
}

template <typename ValueType>
std::ostream& operator <<(std::ostream& os,
                          const PriorityQueue<ValueType>& pq) {
    os << "{";

    // 更快的实现：按堆顺序打印
    // （唯一缺点：不会按“排序后”的优先级顺序打印，
    //  这可能会让学生客户端感到困惑）
    for (int i = 0, len = pq.size(); i < len; i++) {
        if (i > 0) {
            os << ", ";
        }
        os << pq._heap[i].priority << ":";
        writeGenericValue(os, pq._heap[i].value, /* forceQuotes */ true);
    }
    return os << "}";
}

template <typename ValueType>
    void readOne(PriorityQueue<ValueType>& pq, const double& priority, const ValueType& value)
        { pq.enqueue(value, priority); }

template <typename ValueType>
std::istream& operator >>(std::istream& is, PriorityQueue<ValueType>& pq) {
    double priority;
    ValueType element;
    return stanfordcpplib::collections::readPairedCollection(is, pq, priority, element, /* 描述符 */ "PriorityQueue::operator >>", readOne<ValueType>);
}

#endif // _priorityqueue_h
