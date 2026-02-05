#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;

    int l = 0;
    int r = 0;

    if(l > r) swap(l, r);
    
    for (int i = 1; i <= n; i++)
    {
        if(l < k - 1 && l + r + max(l + 1, r) <= m) l++;
        if(r < n - k && l + r + max(l, r + 1) <= m) r++;
    }

    cout << l + r + 1 << endl;
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