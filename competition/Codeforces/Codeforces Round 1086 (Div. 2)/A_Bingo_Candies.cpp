#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;

    vector<vector<int>> s(n + 1, vector<int>(n + 1));
    int Max = 0;
    unordered_map<int, int> count;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> s[i][j];
            count[s[i][j]]++;
            Max = max(Max, count[s[i][j]]);
        }
    }

    if (n == 1)
    {
        cout << "NO" << endl;
        return;
    }

    cout << ((Max > (n - 1) * n ? "NO" : "YES")) << endl;
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