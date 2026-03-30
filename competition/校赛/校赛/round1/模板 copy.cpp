#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m;
    cin >> n >> m;

    int s[60][60] = {0};
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1;j <= n; j++)
        {
            cin >> s[i][j];
        }
    }

    int vi[60][60] = {0};

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            int a = s[i][j];
            int b = s[i][j + 1];

            vi[a][b] = 1;
            vi[b][a] = 1;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        vi[i][i] = 1;
    }

    int count = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if(!vi[i][j])
            {
                count++;
            }
        }
    }

    cout << count / 2 << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}