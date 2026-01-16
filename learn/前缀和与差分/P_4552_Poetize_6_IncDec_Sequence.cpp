#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    vector<int> cf(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cf[i] = s[i] - s[i - 1];
    }

    int a = 0, b = 0;
    for (int i = 2; i <= n; i++)
    {
        if (cf[i] > 0)
        {
            a += cf[i];
        }
        else if (cf[i] < 0)
        {
            b += -cf[i];
        }
    }
    cout << max(a, b) << endl;
    cout << 1 + abs(a - b) << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}