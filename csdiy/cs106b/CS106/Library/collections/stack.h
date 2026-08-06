/*
 * 文件：stack.h
 * -------------
 * 此文件导出 <code>Stack</code> 类，该类实现
 * 按后进先出（LIFO）顺序处理值的集合。
 */

#ifndef _stack_h
#define _stack_h

#include <initializer_list>

#include "error.h"
#include "hashcode.h"
#include "vector.h"

/*
 * 类：Stack<ValueType>
 * -----------------------
 * 此类对一种称为<b><i>栈</i></b>的线性结构建模
 * 其中值只从一端添加和移除。
 * 这种规则产生后进先出（LIFO）的行为
 * 这是栈的定义性特征。基本栈操作
 * 操作包括 <code>push</code>（添加到顶部）和 <code>pop</code>
 * （从顶部移除）。
 */
template <typename ValueType>
class Stack {
public:
    /*
     * 构造函数：Stack
     * 用法：Stack<ValueType> stack;
     * ------------------------------
     * 初始化一个新的空栈。
     */
    Stack() = default;

    /*
     * 构造函数：Stack
     * 用法：Stack<ValueType> stack {1, 2, 3};
     * ----------------------------------------
     * 初始化一个按从底到顶顺序存储给定元素的新栈。
     */
    Stack(std::initializer_list<ValueType> list);

    /*
     * 析构函数：~Stack
     * ------------------
     * 释放与此栈关联的任何堆存储。
     */
    virtual ~Stack() = default;

    /*
     * 方法：clear
     * 用法：stack.clear();
     * ---------------------
     * 从此栈中删除所有元素。
     */
    void clear();

    /*
     * 方法：equals
     * 用法：if (stack.equals(stack2)) ...
     * ------------------------------------
     * 如果此栈包含完全相同的值，则返回 <code>true</code>
     * 与给定的另一个栈相同。
     * 行为与 == 运算符相同。
     */
    bool equals(const Stack<ValueType>& stack2) const;

    /*
     * 方法：isEmpty
     * 用法：if (stack.isEmpty()) ...
     * -------------------------------
     * 如果此栈不包含元素，则返回 <code>true</code>。
     */
    bool isEmpty() const;

    /*
     * 方法：peek
     * 用法：ValueType top = stack.peek();
     * ------------------------------------
     * 返回此栈顶部元素的值，但不移除
     * 它。若在空栈上调用，此方法会报告错误。
     */
    const ValueType& peek() const;

    /*
     * 方法：pop
     * 用法：ValueType top = stack.pop();
     * -----------------------------------
     * 删除并返回此栈的顶部元素。此
     * 若在空栈上调用，此方法会报告错误。
     */
    ValueType pop();

    /*
     * 方法：push
     * 用法：stack.push(value);
     * -------------------------
     * 将指定值压入此栈顶部。
     */
    void push(const ValueType& value);

    /*
     * 方法：size
     * 用法：int n = stack.size();
     * ----------------------------
     * 返回此栈中的值数量。
     */
    int size() const;

    /*
     * 方法：toString
     * 用法：string str = stack.toString();
     * -------------------------------------
     * 将栈转换为可打印的字符串表示。
     */
    std::string toString() const;

    /*
     * 运算符：==
     * 用法：stack1 == stack2
     * -----------------------
     * 如果 <code>stack1</code> 和 <code>stack2</code>，则返回 <code>true</code>
     * 包含相同元素。
     */
    bool operator ==(const Stack& stack2) const;

    /*
     * 运算符：!=
     * 用法：stack1 != stack2
     * -----------------------
     * 如果 <code>stack1</code> 和 <code>stack2</code>，则返回 <code>true</code>
     * 不包含相同元素。
     */
    bool operator !=(const Stack& stack2) const;

    /*
     * 运算符：<、>、<=、>=
     * 用法：if (stack1 < stack2) ...
     * -------------------------------
     * 用于比较两个栈的关系运算符。
     * <、>、<=、>= 运算符要求 ValueType 定义 < 运算符
     * 以便逐对比较各元素。
     */
    bool operator <(const Stack& stack2) const;
    bool operator <=(const Stack& stack2) const;
    bool operator >(const Stack& stack2) const;
    bool operator >=(const Stack& stack2) const;

    /* 私有部分 */

    /**********************************************************************/
    /* 注意：文件中此处以下的所有内容在逻辑上都属于    */
    /* 属于实现细节，客户端无需关注。    */
    /**********************************************************************/

    /*
     * 实现说明：Stack 数据结构
     * ------------------------------------------
     * 实现栈最简单的方法是将元素存储在
     * Vector。这样做意味着动态内存分配的问题
     * 复制构造和复制赋值已由以下对象的实现解决：
     * 底层 Vector 类。
     */

    template <typename T>
    friend int hashCode(const Stack<T>& s);

    template <typename T>
    friend std::ostream& operator <<(std::ostream& os, const Stack<T>& stack);

private:
    Vector<ValueType> _elements;
};

/*
 * Stack 类实现
 * --------------------------
 * Stack 在内部使用 Vector 管理。这种分层设计
 * 使实现极其简单，以至于大多数
 * 这些方法可以各用一行实现。
 */

template <typename ValueType>
Stack<ValueType>::Stack(std::initializer_list<ValueType> list) : _elements(list) {
}

template <typename ValueType>
void Stack<ValueType>::clear() {
    _elements.clear();
}

template <typename ValueType>
bool Stack<ValueType>::equals(const Stack<ValueType>& stack2) const {
    return stanfordcpplib::collections::equals(_elements, stack2._elements);
}

template <typename ValueType>
bool Stack<ValueType>::isEmpty() const {
    return size() == 0;
}

template <typename ValueType>
const ValueType& Stack<ValueType>::peek() const {
    if (isEmpty()) {
        error("Stack::peek: Attempting to peek at an empty stack");
    }
    return _elements[_elements.size() -1];
}

template <typename ValueType>
ValueType Stack<ValueType>::pop() {
    if (isEmpty()) {
        error("Stack::pop: Attempting to pop an empty stack");
    }
    return _elements.remove(_elements.size() -1);
}

template <typename ValueType>
void Stack<ValueType>::push(const ValueType& value) {
    _elements.add(value);
}

template <typename ValueType>
int Stack<ValueType>::size() const {
    return _elements.size();
}

template <typename ValueType>
std::string Stack<ValueType>::toString() const {
    std::ostringstream os;
    os << *this;
    return os.str();
}

template <typename ValueType>
bool Stack<ValueType>::operator ==(const Stack& stack2) const {
    return _elements == stack2._elements;
}

template <typename ValueType>
bool Stack<ValueType>::operator !=(const Stack & stack2) const {
    return _elements != stack2._elements;
}

template <typename ValueType>
bool Stack<ValueType>::operator <(const Stack & stack2) const {
    return _elements < stack2._elements;
}

template <typename ValueType>
bool Stack<ValueType>::operator <=(const Stack & stack2) const {
    return _elements <= stack2._elements;
}

template <typename ValueType>
bool Stack<ValueType>::operator >(const Stack & stack2) const {
    return _elements > stack2._elements;
}

template <typename ValueType>
bool Stack<ValueType>::operator >=(const Stack & stack2) const {
    return _elements >= stack2._elements;
}

template <typename ValueType>
std::ostream& operator <<(std::ostream& os, const Stack<ValueType>& stack) {
    return os << stack._elements;
}

template <typename ValueType>
    void readOne(Stack<ValueType>& stack, const ValueType& value)
        { stack.push(value); }

template <typename ValueType>
std::istream& operator >>(std::istream& is, Stack<ValueType>& stack) {
    ValueType element;
    return stanfordcpplib::collections::readCollection(is, stack, element, /* 描述符 */ "Stack::operator >>", readOne<ValueType>);
}

/*
 * 栈的模板哈希函数。
 * 要求 Stack 中的元素类型具有 hashCode 函数。
 */
template <typename T>
int hashCode(const Stack<T>& s) {
    return hashCode(s._elements);
}

#endif // _stack_h
