#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, q;
    cin >> n >> q;

    string s;
    cin >> s;
    s = " " + s;

    vector<vector<int>> cnt(26, vector<int> (n + 1));
    for (int i = 1; i <= n; i++)
    {
        int c = s[i] - 'a';
        cnt[c][i]++;
    }

    vector<vector<int>> pre(26, vector<int>(n + 2));

    for (int c = 0; c < 26; c++)
    {
        for (int i = 1; i <= n; i++)
        {
            pre[c][i] = pre[c][i - 1] + cnt[c][i];
        }
    }

    vector<vector<int>> sum(26, vector<int>(n + 2));
    vector<vector<int>> mul(26, vector<int>(n + 2));
    for (int c = 0; c < 26; c++)
    {
        for (int i = 1; i <= n; i++)
        {
            sum[c][i] = sum[c][i - 1] + pre[c][i];
            mul[c][i] = mul[c][i - 1] + pre[c][i - 1] * pre[c][i];
        }
    }

    while(q--)
    {
        int l, r, x;
        cin >> l >> r >> x;

        if(x == 1)
        {
            cout << r - l + 1 << endl;
            continue;
        }
        if(x == 2)
        {
            int ans = 0;
            for (int i = 0; i < 26; i++)
            {
                int count = pre[i][r] - pre[i][l - 1];
                ans += count * (count - 1) / 2;
            }
            cout << ans << endl;
            continue;
        }
        if (x == 3)
        {
            int ans = 0;
            int len = r - l + 1;

            for (int c = 0; c < 26; c++)
            {
                // Σ (pre[c][i - 1] - pre[c][l - 1]) * (pre[c][r] - pre[c][i])

                // A = pre[c][l - 1];
                // B = pre[c][r];

                // Σ (pre[c][i - 1] - A) * (B - pre[c][i])

                // Σ ( pre[c][i - 1] * B
                // - pre[c][i - 1] * pre[c][i]
                // - A * B
                // + A * pre[c][i] )

                //   B * Σpre[c][i - 1]
                // - Σ(pre[c][i - 1] * pre[c][i])
                // - A * B * len
                // + A * Σpre[c][i]

                // 需要预处理
                // Σpre[c][i]
                // Σ(pre[c][i - 1] * pre[c][i])

                int A = pre[c][l - 1];
                int B = pre[c][r];

                int s1 = sum[c][r - 1] - (l >= 2 ? sum[c][l - 2] : 0);
                int s2 = mul[c][r] - mul[c][l - 1];
                int s3 = sum[c][r] - sum[c][l - 1];

                ans += B * s1 - s2 - A * B * len + A * s3;
            }

            cout << ans << endl;
            continue;
        }
    }

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