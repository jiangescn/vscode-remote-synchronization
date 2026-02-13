#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int m, n;
    cin >> m >> n;
    for (int i = 1; i <= m; i++)
    {
        int fan = i;
        for (int j = 1; j <= n; j++)
        {
            if (fan & 1)
            {
                if (j & 1)
                {
                    cout << '/';
                }
                else
                {
                    cout << '\\';
                }
            }
            else
            {
                if (j & 1)
                {
                    cout << '\\';
                }
                else
                {
                    cout << '/';
                }
            }
        }
        cout << endl;
    }
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