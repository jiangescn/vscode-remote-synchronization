#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;

    vector<int> s(n + 1);
    int g = 0;

    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        g = __gcd(g, s[i]);
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (s[i] == g) cnt++;
    }

    if (cnt)
    {
        cout << n - cnt << '\n';
        return;
    }

    //////////////////////////////////////////

    const int INF = 1e18;
    vector<int> dis(5001, INF);
    queue<int> q;

    for (int i = 1; i <= n; i++)
    {
        if (dis[s[i]] == INF)
        {
            dis[s[i]] = 0;
            q.push(s[i]);
        }
    }

    while (!q.empty())
    {
        int x = q.front();
        q.pop();

        for (int i = 1; i <= n; i++)
        {
            int y = __gcd(x, s[i]);

            if (dis[y] > dis[x] + 1)
            {
                dis[y] = dis[x] + 1;
                q.push(y);
            }
        }
    }

    cout << dis[g] + n - 1 << '\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}