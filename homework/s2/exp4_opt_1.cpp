#include <cassert>
#include <iostream>
using namespace std;

template <class T>
class Stack
{
private:
    T *data;
    int capacity;
    int top;

public:
    Stack(int size = 50);
    Stack(const Stack<T> &rhs);
    ~Stack();
    Stack<T> &operator=(const Stack<T> &rhs);
    void push(const T &item);
    T pop();
    const T &getTop() const;
    bool isEmpty() const;
    bool isFull() const;
    void clear();
};

template <class T>
Stack<T>::Stack(int size)
{
    assert(size > 0);
    capacity = size;
    data = new T[capacity];
    top = -1;
}

template <class T>
Stack<T>::Stack(const Stack<T> &rhs)
{
    capacity = rhs.capacity;
    top = rhs.top;
    data = new T[capacity];
    for (int i = 0; i <= top; ++i)
        data[i] = rhs.data[i];
}

template <class T>
Stack<T>::~Stack()
{
    delete[] data;
}

template <class T>
Stack<T> &Stack<T>::operator=(const Stack<T> &rhs)
{
    if (this != &rhs)
    {
        if (capacity != rhs.capacity)
        {
            delete[] data;
            capacity = rhs.capacity;
            data = new T[capacity];
        }
        top = rhs.top;
        for (int i = 0; i <= top; ++i)
            data[i] = rhs.data[i];
    }
    return *this;
}

template <class T>
void Stack<T>::push(const T &item)
{
    assert(!isFull());
    data[++top] = item;
}

template <class T>
T Stack<T>::pop()
{
    assert(!isEmpty());
    return data[top--];
}

template <class T>
const T &Stack<T>::getTop() const
{
    assert(!isEmpty());
    return data[top];
}

template <class T>
bool Stack<T>::isEmpty() const
{
    return top == -1;
}

template <class T>
bool Stack<T>::isFull() const
{
    return top == capacity - 1;
}

template <class T>
void Stack<T>::clear()
{
    top = -1;
}

int main()
{
    long long number;
    Stack<int> stack(64);

    cout << "Input a decimal integer: ";
    cin >> number;

    if (number == 0)
    {
        cout << "Binary result: 0" << endl;
        return 0;
    }

    if (number < 0)
    {
        cout << "Binary result: -";
        number = -number;
    }
    else
    {
        cout << "Binary result: ";
    }

    while (number > 0)
    {
        stack.push(number % 2);
        number /= 2;
    }

    while (!stack.isEmpty())
        cout << stack.pop();
    cout << endl;

    return 0;
}
