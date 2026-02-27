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

    int ans = 0;
    int ok = 1;
    for (int i = 1; i <= n; i++)
    {
        if((s[i] & 1) ^ (i & 1))
        {
            ok = 0;
        }
    }
    if(ok) ans = 1;
    ok = 1;
    for (int i = 1; i <= n; i++)
    {
        if((s[i] & 1) ^ ((i - 1) & 1))
        {
            ok = 0;
        }
    }
    if(ok) ans = 1;

    cout << (ans ? "YES" : "NO") << endl;
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