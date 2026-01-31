#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    vector<int> b(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
    }
    int Max = 0;
    vector<int> s(n + 1);
    for (int i = n; i >= 1; i--)
    {
        Max = max({Max, a[i], b[i]});
        s[i] = Max;
    }

    for (int i = 1; i <= n; i++)
    {
        s[i] = s[i] + s[i-1];
    }

    while(q--)
    {
        int l, r;
        cin >> l >> r;
        cout << s[r] - s[l-1] << " ";
    }
    cout << endl;
    return ;
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