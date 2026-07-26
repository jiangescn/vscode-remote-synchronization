#include <cassert>
#include <iostream>
using namespace std;

template <class T>
class Array
{
private:
    T* data;
    int num;

public:
    Array(int n = 0);
    Array(const Array<T>& rhs);
    ~Array();
    Array<T>& operator=(const Array<T>& rhs);
    T& operator[](int index);
    const T& operator[](int index) const;
    operator T*();
    operator const T*() const;
    int getCapacity() const;
    void resize(int n);
};

template <class T>
Array<T>::Array(int n)
{
    assert(n >= 0);
    num = n;
    data = (num == 0) ? 0 : new T[num];
}

template <class T>
Array<T>::Array(const Array<T>& rhs)
{
    num = rhs.num;
    data = (num == 0) ? 0 : new T[num];
    for (int i = 0; i < num; ++i)
        data[i] = rhs.data[i];
}

template <class T>
Array<T>::~Array()
{
    delete[] data;
}

template <class T>
Array<T>& Array<T>::operator=(const Array<T>& rhs)
{
    if (this != &rhs)
    {
        if (num != rhs.num)
        {
            delete[] data;
            num = rhs.num;
            data = (num == 0) ? 0 : new T[num];
        }
        for (int i = 0; i < num; ++i)
            data[i] = rhs.data[i];
    }
    return *this;
}

template <class T>
T& Array<T>::operator[](int index)
{
    assert(index >= 0 && index < num);
    return data[index];
}

template <class T>
const T& Array<T>::operator[](int index) const
{
    assert(index >= 0 && index < num);
    return data[index];
}

template <class T>
Array<T>::operator T*()
{
    return data;
}

template <class T>
Array<T>::operator const T*() const
{
    return data;
}

template <class T>
int Array<T>::getCapacity() const
{
    return num;
}

template <class T>
void Array<T>::resize(int n)
{
    assert(n >= 0);
    if (n == num)
        return;

    T* newData = (n == 0) ? 0 : new T[n];
    int copyCount = (n < num) ? n : num;
    for (int i = 0; i < copyCount; ++i)
        newData[i] = data[i];

    delete[] data;
    data = newData;
    num = n;
}

template <class T>
void bubbleSort(T data[], int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; ++j)
        {
            if (data[j] > data[j + 1])
            {
                T temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

int main()
{
    Array<int> numbers(10);

    cout << "Input 10 integers: \n";
    for (int i = 0; i < numbers.getCapacity(); ++i)
        cin >> numbers[i];

    bubbleSort(static_cast<int*>(numbers), numbers.getCapacity());

    cout << "Sorted result: \n";
    for (int i = 0; i < numbers.getCapacity(); ++i)
        cout << numbers[i] << ' ';
    cout << endl;

    return 0;
}
