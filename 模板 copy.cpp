#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <stack>
using namespace std;
#define int long long

vector<vector<int>> s;
vector<int> idx;
vector<int> reidx;
int timer = 1;

vector<int> sz;


int dfs(int x)
{
    idx[x] = timer++;

    if(s[x].size() == 0) return 1;

    for (int i = 0; i < s[x].size(); i++)
    {
        sz[x] += dfs(s[x][i]);
    }

    return sz[x];
}

void solve()
{
    int n, q;
    cin >> n >> q;

    s.resize(n + 1);
    idx.resize(n + 1);
    reidx.resize(n + 1);
    sz.resize(n + 1, 1);
    for (int i = 2; i <= n; i++)
    {
        int a;
        cin >> a;
        s[a].push_back(i);
    }

    for (int i = 1; i < s.size(); i++)
    {
        sort(s[i].begin(), s[i].end());
    }


    dfs(1);

    for (int i = 1; i <= n; i++)
    {
        reidx[idx[i]] = i;
    }

    while(q--)
    {
        int u, k;
        cin >> u >> k;

        if(k > sz[u])
        {
            cout << -1 << endl;
            continue;
        }

        cout << reidx[idx[u] + k - 1] << endl;
    }

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