#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    vector<int> pre(n + 1);
    for (int i = 1; i <= n; i++)
    {
        pre[i] = pre[i - 1] + s[i];
    }

    while (q--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int x;
            cin >> x;
            int del = s[x] - s[x+1];
            swap(s[x], s[x+1]);
            pre[x] -= del;
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << pre[r] - pre[l - 1] << endl;
        }
    }
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