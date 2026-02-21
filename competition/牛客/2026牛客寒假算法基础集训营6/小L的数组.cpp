#include <bits/stdc++.h>
using namespace std;
#define int long long

int n;
vector<int> a, b;
const int MAX = 2048;

vector<vector<int>> vi;

int dfs(int i, int x)
{
    if (i == n) return x;
    int ans = vi[i][x];
    if (ans != -1) return ans;

    int y1 = max(x - a[i], 0ll);
    int v1 = dfs(i + 1, y1);

    int y2 = x ^ b[i];
    int v2 = dfs(i + 1, y2);

    if (v1 >= v2)
    {
        ans = v1;
        vi[i][x] = v1;
    }
    else
    {
        ans = v2;
        vi[i][x] = v2;
    }
    return ans;
}

void solve()
{
    cin >> n;
    a.resize(n);
    b.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    vi.resize(n + 1, vector<int>(MAX, -1));
    cout << dfs(0, 0) << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
