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
    multiset<int> a;
    for (int l = 1, r = 1; r <= n; r++)
    {
        a.insert(s[r]);
        while (*a.rbegin() - *a.begin() > 1)
        {
            a.erase(a.find(s[l++]));
        }
        // r 结尾的的最长子段
        ans += r - l + 1;
    }

    cout << ans << endl;
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