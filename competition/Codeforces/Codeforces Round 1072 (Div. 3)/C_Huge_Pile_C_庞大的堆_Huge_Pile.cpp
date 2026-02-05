#include <bits/stdc++.h>
using namespace std;
#define int long long
map<int, int> vi;
int n, k;

void dfs(int x, int deep)
{
    if(vi[x])
    {
        return;
    }
    vi[x] = deep;
    if (x <= 1 || x == k )
    {
        return;
    }
    dfs(x / 2, deep + 1);
    if (x & 1)
    {
        dfs(x / 2 + 1, deep + 1);
    }
}

void solve()
{
    cin >> n >> k;
    vi.clear();

    if (n == k)
    {
        cout << 0 << endl;
        return;
    }

    dfs(n, 0);

    // for (int i = 1; i <= n; i++)
    // {
    //     cout << vi[i] << " ";
    // } cout << endl;

    cout << (vi[k] ? vi[k] : -1) << endl;
    return;
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