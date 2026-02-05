#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int s, k, m;
    cin >> s >> k >> m;

    int yu = (m / k) & 1 ? min(k, s) : s;
    int ans = max(0ll, yu - (m - m / k * k));

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