#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k, p, m;
    cin >> n >> k >> p >> m;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    int cur = m;
    int x = s[p];

    int d = p - k;
    if(d > 0)
    {
        vector<int> pre(1);
        for (int i = 1; i < p; i++)
        {
            pre.push_back(s[i]);
        }
        sort(pre.begin() + 1, pre.end());

        for (int i = 1; i <= d; i++)
        {
            cur -= pre[i];
        }

        if(cur <= 0)
        {
            cout << 0 << endl;
            return;
        }
    }

    cur -= x;
    if (cur < 0)
    {
        cout << 0 << '\n';
        return;
    }

    vector<int> ss;
    for (int i = 1; i <= n; i++)
    {
        if (i == p)
            continue;
        ss.push_back(s[i]);
    }
    sort(ss.begin(), ss.end());
    int once = x;
    for (int i = 0; i < n - k; i++)
    {
        once += ss[i];
    }

    cout << cur / once + 1 << endl;
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