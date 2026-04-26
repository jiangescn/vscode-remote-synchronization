#include <bits/stdc++.h>
using namespace std;
#define int long long

const int INF = 4e18;

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<int> v(n + 2);
    for (int i = 1; i <= n; i++)
    {
        cin >> v[i];
    }

    vector<int> premn(n + 2), premx(n + 2);
    vector<int> sufmn(n + 2), sufmx(n + 2);

    premn[0] = INF;
    premx[0] = -INF;

    for (int i = 1; i <= n; i++)
    {
        premn[i] = min(premn[i - 1], v[i]);
        premx[i] = max(premx[i - 1], v[i]);
    }

    sufmn[n + 1] = INF;
    sufmx[n + 1] = -INF;

    for (int i = n; i >= 1; i--)
    {
        sufmn[i] = min(sufmn[i + 1], v[i]);
        sufmx[i] = max(sufmx[i + 1], v[i]);
    }

    int ans1 = -INF;
    int ans2 = INF;

    for (int l = 1; l + k - 1 <= n; l++)
    {
        int r = l + k - 1;

        int mn = min(premn[l - 1], sufmn[r + 1]);
        int mx = max(premx[l - 1], sufmx[r + 1]);

        int range = mx - mn;

        ans1 = max(ans1, range);
        ans2 = min(ans2, range);
    }

    cout << ans1 << ' ' << ans2 << endl;
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}