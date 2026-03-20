#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m;
    cin >> n >> m;

    string tar = "meituan";
    int p = 0;

    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;

        if (p < (int)tar.size())
        {
            for (char c : s)
            {
                if (c == tar[p])
                {
                    p++;
                    break;
                }
            }
        }
    }

    if (p == tar.size())
        cout << "YES\n";
    else
        cout << "NO\n";
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}