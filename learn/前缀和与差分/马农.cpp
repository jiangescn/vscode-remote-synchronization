#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> s(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> s[i][j];
        }
    }
    int ans = 0;

    // 构建前缀和
    vector<vector<int>> pre(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            pre[i][j] = s[i][j] + pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
        }
    }

    //枚举交汇点
    for (int i = 1; i <= n - 1; i++)
    {
        for (int j = 1; j <= n - 1; j++)
        {
            //↖️ ↘️
            //左上区间
            for (int x1 = 1; x1 <= i; x1++)
            {
                for (int y1 = 1; y1 <= j; y1++)
                {
                    //右下区间
                    for (int x2 = i + 1; x2 <= n; x2++)
                    {
                        for (int y2 = j + 1; y2 <= n; y2++)
                        {
                            int sum1 = pre[i][j] - pre[i][y1 - 1] - pre[x1 - 1][j] + pre[x1 - 1][y1 - 1];
                            int sum2 = pre[x2][y2] - pre[i][y2] - pre[x2][j] + pre[i][j];
                            if (sum1 == sum2)
                                ans++;
                        }
                    }
                }
            }

            //↗️ ↙️
            //右上区间
            for (int x1 = 1; x1 <= i; x1++)
            {
                for (int y2 = j + 1; y2 <= n; y2++)
                {
                    //左下去见
                    for (int x2 = i + 1; x2 <= n; x2++)
                    {
                        for (int y1 = 1; y1 <= j; y1++)
                        {
                            int sumNE = pre[i][y2] - pre[i][j] - pre[x1 - 1][y2] + pre[x1 - 1][j];

                            int sumSW = pre[x2][j] - pre[i][j] - pre[x2][y1 - 1] + pre[i][y1 - 1];

                            if (sumNE == sumSW)
                                ans++;
                        }
                    }
                }
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
    while (t--)
    {
        solve();
    }
    return 0;
}