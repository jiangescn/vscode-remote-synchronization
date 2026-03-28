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

    vector<int> stk;
    vector<int> L(n + 1), R(n + 1);

    for (int i = 1; i <= n; i++)
    {
        while (!stk.empty() && s[stk.back()] < s[i])
            stk.pop_back();
        L[i] = stk.size();
        stk.push_back(i);
    }

    stk.clear();

    for (int i = n; i >= 1; i--)
    {
        while (!stk.empty() && s[stk.back()] < s[i])
            stk.pop_back();
        R[i] = stk.size();
        stk.push_back(i);
    }

    int ans = n;
    for (int i = 1; i <= n; i++)
    {
        ans = min(ans, n - (L[i] + R[i] + 1));
    }
    cout << ans << endl;
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