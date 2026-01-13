#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int n;
    cin >> n;
    int sum = 0;
    while (n % 2 == 0)
    {
        n /= 2;
    }
    
    for (int i = 1; i * (i + 1) <= 2 * n; i += 2)
    {
        if (n % i == 0)
        {
            sum++;
        }
    }

    for (int i = 2; i * (i + 1) <= 2 * n; i += 2)
    {
        if ((n - i / 2) % i == 0)
        {
            sum++;
        }
    }
    cout << sum << endl;
} 