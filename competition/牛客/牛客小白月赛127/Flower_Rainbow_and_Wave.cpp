#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    if (n <= 2 || n == 4)
    {
        cout << "-1" << endl;
        return;
    }
    if (n % 2 == 1)
    {
        for (int i = 1; i <= n / 2 + 1; i++)
        {
            cout << i << " ";
        }
        for (int i = n / 2; i >= 1; i--)
        {
            cout << i << " ";
        }
    }
    else
    {
        cout << "1 2 1 ";
        n -= 3;
        for (int i = 1; i <= n / 2 + 1; i++)
        {
            cout << i << " ";
        }
        for (int i = n / 2; i >= 1; i--)
        {
            cout << i << " ";
        }
    }
    cout << endl;
    return;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}