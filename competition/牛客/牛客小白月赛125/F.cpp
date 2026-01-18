#include <bits/stdc++.h>
using namespace std;
#define int long long

void solv()
{
    int n;
    cin >> n;
    if (n == 1 || n == 2)
    {
        cout << -1 << '\n';
        return;
    }

    if (n & 1)
    {
        cout << n;
        for (int i = 1; i < n; i++)
        {
            cout << " " << i;
        }
        cout << '\n';
        return;
    }

    if ((n / 2 + 2) % 3 != 0)
    {
        for (int i = 1; i <= n / 2; i++)
        {
            cout << (n / 2 + i) << " " << i;
            if (i != n / 2)
            {
                cout << " ";
            }
        }
        cout << '\n';
    }
    else
    {
        cout << 4 << " " << n << " " << 1 << " " << 2 << " " << 3;
        for (int i = 5; i < n; i++)
        {
            cout << " " << i;
        }
        cout << '\n';
    }
}

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solv();
    }
    return 0;
}
