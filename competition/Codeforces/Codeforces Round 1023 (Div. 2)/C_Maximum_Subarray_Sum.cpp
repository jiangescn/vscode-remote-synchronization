#include <bits/stdc++.h>
using namespace std;
#define int long long
#define itn int

const int INF = 1000000000000000000LL;
const int NEG = -INF;

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<int> s(n + 1);

    string ss;
    cin >> ss;
    ss = " " + ss;

    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    int have0 = 0;

    for (itn i = 1; i <= n; i++)
    {
        if (ss[i] == '0')
        {
            have0 = 1;
        }
    }

    vector<int> dp(n + 1);
    int Max_sub = 0;

    for (itn i = 1; i <= n; i++)
    {
        if (ss[i] == '1')
        {
            dp[i] = max(dp[i - 1] + s[i], s[i]);
        }
        else
        {
            dp[i] = 0;
        }

        Max_sub = max(Max_sub, dp[i]);
    }

    if (Max_sub > k)
    {
        cout << "No\n";
        return;
    }

    if (Max_sub == k)
    {
        cout << "Yes\n";

        for (int i = 1; i <= n; i++)
        {
            if (ss[i] == '1')
            {
                cout << s[i] << " ";
            }
            else
            {
                cout << NEG << " ";
            }
        }

        cout << "\n";
        return;
    }

    if (!have0)
    {
        cout << "No\n";
        return;
    }

    int found = 0;

    for (int i = 1; i <= n; i++)
    {
        if (ss[i] == '0')
        {
            int left_sum = 0;
            int now = 0;

            for (int j = i - 1; j >= 1 && ss[j] == '1'; j--)
            {
                now += s[j];
                left_sum = max(left_sum, now);
            }

            int right_sum = 0;
            now = 0;

            for (int j = i + 1; j <= n && ss[j] == '1'; j++)
            {
                now += s[j];
                right_sum = max(right_sum, now);
            }

            int connect_sum = left_sum + right_sum;

            s[i] = k - connect_sum;
            ss[i] = '1';

            found = 1;
            break;
        }
    }

    cout << "Yes\n";

    for (int i = 1; i <= n; i++)
    {
        if (ss[i] == '1')
        {
            cout << s[i] << " ";
        }
        else
        {
            cout << NEG << " ";
        }
    }

    cout << "\n";
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}