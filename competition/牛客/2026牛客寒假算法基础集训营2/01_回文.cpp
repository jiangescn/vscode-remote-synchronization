#include <bits/stdc++.h>
using namespace std;
const int N = 1000010;

void solve()
{
    int n, m;
    cin >> n >> m;
    // n = 2, m = 2;
    vector<vector<bool>> s(n + 1, vector<bool>(m + 1, false));

    int o = 0, l = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            char x;
            cin >> x;
            s[i][j] = (x == '1');
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s[i][j])
            {
                l++;
            }
            else
            {
                o++;
            }
        }
    }

    // cout << "1:" << l << endl;
    // cout << "0:" << o << endl;
    
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if((s[i][j] == 1 && l == 1) || (s[i][j] == 0 && o == 1))
            {
                cout << 'N';
            }
            else
            {
                cout << 'Y';
            }
        }
        cout << '\n';
    }
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