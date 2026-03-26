#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;
    int count = n;

    if (n < k)
    {
        cout << "No" << endl;
        return;
    }
    if (n < k + 1 && n < 4)
    {
        cout << "No" << endl;
        return;
    }

    if(n == k)
    {
        cout << "Yes" << endl;
        cout << 1 << " " << 1 << endl;
        cout << 0 << " " << 1 << endl;
        cout << 1 << " " << 0 << endl;
        cout << 0 << " " << 0 << endl;
        for (int i = 2; i <= k - 3; i++)
        {
            cout << 0 << " " << i << endl;
        }
        return;
    }

    cout << "Yes" << endl;

    for (int i = 0; i <= k; i++)
    {
        cout << 0 << " " << i << endl;
        count--;
    }

    while (count--)
    {
        cout << 10 << " " << count * 5 << endl;
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    while (t--)
    {
        solve();
    }
    return 0;
}