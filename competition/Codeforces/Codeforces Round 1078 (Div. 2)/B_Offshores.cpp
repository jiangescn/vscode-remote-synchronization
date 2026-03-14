#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, x, y;
    cin >> n >> x >> y;

    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    vector<int> chu = s;
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        chu[i] = s[i] / x * y;
        sum += chu[i];
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans = max(ans, sum - chu[i] + s[i]);
    }
    
    cout << ans << endl;
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