#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int two = 2;

    int n;
    cin >> n;

    if(n % 2 == 1)
    {
        cout << "Bob" << endl;
        return 0;
    }

    while(n > two)
    {
        two *= 2;
    }

    if(n == two)
    {
        cout << "Alice" << endl;
    }
    else
    {
        cout << "Bob" << endl;
    }

    return 0;
}