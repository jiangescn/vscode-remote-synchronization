#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve ()
{
    int n, m;
    cin >> n >> m;

    vector<vector<char>> s(n + 1, vector<char> (m + 1));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> s[i][j];
        }
    }

    if (n == 1 || m == 1) {
        cout << "NO\n";
        return;
    }

    int ok1 = 1;
    for (int i = 1; i <= m; i++)
    {
        if(s[1][i] == '#') ok1 = 0;
    }
    for (int i = 1; i <= n; i++)
    {
        if(s[i][m] == '#') ok1 = 0;
    }


    int ok2 = 1;
    for (int i = 1; i <= m; i++)
    {
        if(s[n][i] == '#') ok2 = 0;
    }
    for (int i = 1; i <= n; i++)
    {
        if(s[i][1] == '#') ok2 = 0;
    }

    if(ok1 || ok2)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
}

int32_t main ()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int _ = 1;
    // cin >> _;
    while (_--) {
        solve();
    }
    return 0;
}