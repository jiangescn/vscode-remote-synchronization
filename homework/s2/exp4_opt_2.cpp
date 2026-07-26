#include <cassert>
#include <iostream>
using namespace std;

template <class T>
class Queue
{
private:
    T *data;
    int capacity;
    int front;
    int rear;
    int count;

public:
    Queue(int size = 50);
    Queue(const Queue<T> &rhs);
    ~Queue();
    Queue<T> &operator=(const Queue<T> &rhs);
    void enqueue(const T &item);
    T dequeue();
    const T &getFront() const;
    bool isEmpty() const;
    bool isFull() const;
    void clear();
    int getSize() const;
};

template <class T>
Queue<T>::Queue(int size)
{
    assert(size > 0);
    capacity = size;
    data = new T[capacity];
    front = 0;
    rear = 0;
    count = 0;
}

template <class T>
Queue<T>::Queue(const Queue<T> &rhs)
{
    capacity = rhs.capacity;
    data = new T[capacity];
    front = 0;
    rear = rhs.count % capacity;
    count = rhs.count;
    for (int i = 0; i < count; ++i)
        data[i] = rhs.data[(rhs.front + i) % rhs.capacity];
}

template <class T>
Queue<T>::~Queue()
{
    delete[] data;
}

template <class T>
Queue<T> &Queue<T>::operator=(const Queue<T> &rhs)
{
    if (this != &rhs)
    {
        if (capacity != rhs.capacity)
        {
            delete[] data;
            capacity = rhs.capacity;
            data = new T[capacity];
        }
        front = 0;
        rear = rhs.count % capacity;
        count = rhs.count;
        for (int i = 0; i < count; ++i)
            data[i] = rhs.data[(rhs.front + i) % rhs.capacity];
    }
    return *this;
}

template <class T>
void Queue<T>::enqueue(const T &item)
{
    assert(!isFull());
    data[rear] = item;
    rear = (rear + 1) % capacity;
    ++count;
}

template <class T>
T Queue<T>::dequeue()
{
    assert(!isEmpty());
    T item = data[front];
    front = (front + 1) % capacity;
    --count;
    return item;
}

template <class T>
const T &Queue<T>::getFront() const
{
    assert(!isEmpty());
    return data[front];
}

template <class T>
bool Queue<T>::isEmpty() const
{
    return count == 0;
}

template <class T>
bool Queue<T>::isFull() const
{
    return count == capacity;
}

template <class T>
void Queue<T>::clear()
{
    front = 0;
    rear = 0;
    count = 0;
}

template <class T>
int Queue<T>::getSize() const
{
    return count;
}

int main()
{
    const int capacity = 10;
    Queue<int> queue(capacity);
    int n;

    cout << "Input element count (1-10): \n";
    cin >> n;
    if (n < 1)
        n = 1;
    if (n > capacity)
        n = capacity;

    cout << "Input " << n << " integers: \n";
    for (int i = 0; i < n; ++i)
    {
        int value;
        cin >> value;
        queue.enqueue(value);
    }

    cout << "Front element: " << queue.getFront() << endl;
    cout << "Dequeue order: ";
    while (!queue.isEmpty())
        cout << queue.dequeue() << ' ';
    cout << endl;

    return 0;
}
