#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;

    vector<int> vi(2 * n + 1);

    vector<vector<int>> s(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> s[i][j];
            vi[s[i][j]] = 1;
        }
    }

    for (int i = 1; i <= 2 * n; i++)
    {
        if (!vi[i])
            cout << i << " ";
    }

    for (int i = 1; i <= n; i++)
    {
        cout << s[i][1] << " ";
    }

    for (int j = 2; j <= n; j++)
    {
        cout << s[n][j] << " ";
    }

    cout << endl;
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