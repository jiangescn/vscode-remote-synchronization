#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<vector<char>> s(n + 2, vector<char>(n + 2, 0));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> s[i][j];
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (s[i][j] == '*' && s[i - 1][j] == '*' && s[i + 1][j] == '*' )
            {
                if(s[i][j+1] == '*' || s[i][j - 1] == '*')
                {
                    cout << "T" << endl;
                    return;
                }
                else
                {
                    cout << "L" << endl;
                    return;
                }
            }
            else if (s[i][j] == '*' && s[i][j + 1] == '*' && s[i][j - 1] == '*')
            {
                if (s[i + 1][j] == '*' || s[i - 1][j] == '*')
                {
                    cout << "T" << endl;
                    return;
                }
                else
                {
                    cout << "L" << endl;
                    return;
                }
            }
        }
    }
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