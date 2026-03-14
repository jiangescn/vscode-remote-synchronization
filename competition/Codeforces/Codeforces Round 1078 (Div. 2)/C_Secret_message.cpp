#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<string> s(k + 1);
    for (int i = 1; i <= k; i++)
    {
        cin >> s[i];
        s[i] = ' ' + s[i];
    }

    vector<vector<bool>> data(n + 1, vector<bool>(26, false));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= k; j++)
        {
            data[i][s[j][i] - 'a'] = true;
        }
    }

    vector<int> candi;
    for (int i = 1; i <= n; i++)
    {
        if (n % i == 0)
        {
            candi.push_back(i);
        }
    }

    for (int idx = 0; idx < (int)candi.size(); idx++)
    {
        //一个小节d
        int d = candi[idx];
        string base = " ";
        bool ok = true;

        for (int r = 1; r <= d; r++)
        {
            int choose = -1;

            for (int c = 0; c < 26; c++)
            {
                bool good = true;
                for (int p = r; p <= n; p += d)
                {
                    if (!data[p][c])
                    {
                        good = false;
                        break;
                    }
                }
                if (good)
                {
                    choose = c;
                    break;
                }
            }

            if (choose == -1)
            {
                ok = false;
                break;
            }
            base.push_back(char('a' + choose));
        }

        if (ok)
        {
            string ans;
            for (int i = 1; i <= n; i++)
            {
                ans.push_back(base[(i - 1) % d + 1]);
            }
            cout << ans << '\n';
            return;
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