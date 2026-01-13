#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin >> n;

    if (n < 5)
    {
        cout << -1 << endl;
        return 0;
    }

    int bian = n / 2 + 1;

    cout << n + 1 << endl;

    cout << 1 << " " << 2 << endl;
    cout << 1 << " " << bian << endl;
    cout << 1 << " " << bian + 1 << endl;
    cout << 1 << " " << n << endl;

    for (int i = 2; i < bian; i++)
    {
        cout << i << " " << i + 1 << endl;
    }
    for (int i = bian + 1; i < n; i++)
    {
        cout << i << " " << i + 1 << endl;
    }
    return 0;
}