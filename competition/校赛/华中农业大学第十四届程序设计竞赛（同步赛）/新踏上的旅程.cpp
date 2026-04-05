#include <bits/stdc++.h>
using namespace std;
#define int long long
#define itn int

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> b(m + 1);
    for (int i = 1; i <= m; i++)
    {
        cin >> b[i];
    }
    vector<int> r(m + 1);
    for (int i = 1; i <= m; i++)
    {
        cin >> r[i];
    }

    vector<vector<int>> s(m + 1, vector<int>(n + 1));
    vector<int> smax(m + 1);
    for (int i = 1; i <= m; i++)
    {
        int Max = 0;
        for (int j = 1; j <= n; j++)
        {
            cin >> s[i][j];
            Max = max(Max, s[i][j]);
        }
        smax[i] = Max;
    }

    vector<int> x(n + 1);
    vector<int> y(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> x[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> y[i];
    }

    vector<vector<int>> score(m + 1, vector<int>(n + 1));
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (s[i][j] == -1)
            {
                score[i][j] = 0;
                continue;
            }
            if (smax[i] == 0)
            {
                score[i][j] = b[i];
            }
            else
            {
                score[i][j] = b[i] + r[i] * s[i][j] / smax[i];
            }
        }
    }

    vector<double> scorend(n + 1);
    for (int j = 1; j <= n; j++)
    {
        vector<int> tmp;
        for (int i = 1; i <= m; i++)
        {
            tmp.push_back(score[i][j]);
        }

        sort(tmp.begin(), tmp.end(), greater<int>());

        long long sum = 0;
        for (int t = 0; t < k; t++)
        {
            sum += tmp[t];
        }

        scorend[j] = (double)sum / k;
        scorend[j] = min(scorend[j], 100.0);
    }

    vector<int> scoretd(n + 1);
    for (int i = 1; i <= n; i++)
    {
        scoretd[i] = x[i] / 60 + y[i];
        scoretd[i] = min(scoretd[i], 100ll);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (scoretd[i] >= 50 && scorend[i] >= 50)
        {
            if (scoretd[i] >= 60 || scorend[i] >= 60)
            {
                ans++;
            }
        }
    }

    cout << ans << endl;
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