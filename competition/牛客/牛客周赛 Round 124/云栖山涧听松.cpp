#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> s(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        s[a].push_back(b);
        s[b].push_back(a);
    }
    int count = 0;
    for (int i = 1; i <= n; i++)
    {
        if(s[i].size() == 1)
        {
            count++;
        }
    }
    //cout << "count:" << count << endl;
    int ans = count / 2;
    if(count % 2)ans++;
    cout << ans << endl;
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