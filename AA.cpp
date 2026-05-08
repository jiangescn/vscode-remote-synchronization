#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;

    map<array<int, 2>, int> s;
    for (int i = 1; i <= k; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        s[{a, b}] = c;
    }

    
}  

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;
    while (T--)
        solve();

    return 0;
}