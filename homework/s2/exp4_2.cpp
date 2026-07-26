#include <iostream>
using namespace std;

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

template <class T>
void printArray(const T data[], int n)
{
    for (int i = 0; i < n; ++i)
        cout << data[i] << ' ';
    cout << endl;
}

int main()
{
    const int intCount = 10;
    const int charCount = 10;
    int numbers[intCount];
    char letters[charCount];

    cout << "Input 10 integers: \n";
    for (int i = 0; i < intCount; ++i)
        cin >> numbers[i];

    cout << "Input 10 characters: \n";
    for (int i = 0; i < charCount; ++i)
        cin >> letters[i];

    bubbleSort(numbers, intCount);
    bubbleSort(letters, charCount);

    cout << "Sorted integers: ";
    printArray(numbers, intCount);
    cout << "Sorted characters: ";
    printArray(letters, charCount);

    return 0;
}
