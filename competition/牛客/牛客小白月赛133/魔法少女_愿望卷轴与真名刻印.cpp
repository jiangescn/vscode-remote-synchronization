#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    string tar1 = "awdec";
    string tar2 = "Fantasy_Blue";

    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;
    s = " " + s;

    int len1 = tar1.size(); // 5
    int len2 = tar2.size(); // 12

    if (n < len1 + len2)
    {
        cout << "No" << endl;
        return;
    }

    if (k >= len1 + len2)
    {
        cout << "Yes" << endl;
        return;
    }

    const int INF = 1e18;

    vector<int> cost1(n + 2, INF);
    vector<int> cost2(n + 2, INF);

    for (int i = 1; i + len1 - 1 <= n; i++)
    {
        int cnt = 0;
        for (int j = 0; j < len1; j++)
        {
            if (s[i + j] != tar1[j]) cnt++;
        }
        cost1[i] = cnt;
    }

    for (int i = 1; i + len2 - 1 <= n; i++)
    {
        int cnt = 0;
        for (int j = 0; j < len2; j++)
        {
            if (s[i + j] != tar2[j]) cnt++;
        }
        cost2[i] = cnt;
    }

    vector<int> pre1(n + 2, INF);
    vector<int> pre2(n + 2, INF);

    for (int i = 1; i <= n; i++)
    {
        pre1[i] = min(pre1[i - 1], cost1[i]);
        pre2[i] = min(pre2[i - 1], cost2[i]);
    }

    int ans = INF;

    for (int i = 1; i + len2 - 1 <= n; i++)
    {
        if (i - len1 >= 1)
        {
            ans = min(ans, pre1[i - len1] + cost2[i]);
        }
    }

    for (int i = 1; i + len1 - 1 <= n; i++)
    {
        if (i - len2 >= 1)
        {
            ans = min(ans, pre2[i - len2] + cost1[i]);
        }
    }

    if (ans <= k)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
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