#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> s(3, vector<int>(n + 2));
    for (int i = 1; i <= 2; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> s[i][j];
        }
    }

    vector<int> premax(n + 2);
    for (int i = 1; i <= n; i++)
    {
        premax[i] = max(premax[i - 1], s[1][i]);
    }
    vector<int> premin(n + 2, INT_MAX);
    for (int i = 1; i <= n; i++)
    {
        premin[i] = min(premin[i - 1], s[1][i]);
    }

    vector<int> sufmax(n + 3);
    for (int i = n; i >= 1; i--)
    {
        sufmax[i] = max(sufmax[i + 1], s[2][i]);
    }
    vector<int> sufmin(n + 3, INT_MAX);
    for (int i = n; i >= 1; i--)
    {
        sufmin[i] = min(sufmin[i + 1], s[2][i]);
    }

    vector<int> best(2 * n + 2, INT_MAX);
    for (int i = 1; i <= n; i++)
    {
        int Min = min(premin[i], sufmin[i]);
        int Max = max(premax[i], sufmax[i]);

        best[Min] = min(best[Min], Max);
    }
    for (int l = 2 * n; l >= 1; l--)
    {
        best[l] = min(best[l], best[l + 1]);
    }

    int ans = 0;
    for (int l = 1; l <= 2 * n; l++)
    {
        if (best[l] != INT_MAX)
        {
            ans += 2 * n - best[l] + 1;
        }
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