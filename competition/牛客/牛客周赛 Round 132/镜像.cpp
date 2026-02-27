#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MAXV = 1000000;

int re(int x)
{
    int r = 0;
    while (x > 0)
    {
        r = r * 10 + (x % 10);
        x /= 10;
    }
    return r;
}

void solve()
{
    vector<int> vi(MAXV + 1, 0);
    vector<int> deep(MAXV + 1, 0);
    int a, b, k;
    cin >> a >> b >> k;

    if (a == b)
    {
        cout << 0 << '\n';
        return;
    }

    queue<int> q;
    q.push(a);
    deep[a] = 0;
    vi[a] = 1;
    int ans = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        int d = deep[u];

        //+
        int v1 = u + k;
        if (v1 <= MAXV && !vi[v1])
        {
            deep[v1] = d + 1;
            vi[v1] = 1;
            if (v1 == b)
            {
                ans = deep[v1];
                break;
            }
            q.push(v1);
        }

        // 反转
        if (u % 10 != 0)
        {
            int v2 = re(u);
            if (v2 <= MAXV && !vi[v2])
            {
                deep[v2] = d + 1;
                vi[v2] = 1;
                if (v2 == b)
                {
                    ans = deep[v2];
                    break;
                }
                q.push(v2);
            }
        }
    }

    cout << ans << '\n';
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