#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MAXN = 5001;
const int MAXM = 200001;

int father[MAXN];

int find(int i)
{
    if(i != father[i])
    {
        father[i] = find(father[i]);
    }
    return father[i];
}

bool un(int x, int y)
{
    int fx = find(x);
    int fy = find(y);
    if(fx != fy)
    {
        father[fx] = fy;
        return true;
    }
    else
    {
        return false;
    }
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> edges(m + 1, vector<int> (3, 0));
    for (int i = 1; i <= n; i++)
    {
        father[i] = i;
    }

    for (int i = 1; i <= m; i++)
    {
        int x, y, z;
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }

    sort(edges.begin() + 1, edges.end(), [](vector<int> a, vector<int> b)
         { return a[2] < b[2]; });

    int ans = 0;
    int edgeCnt = 0;

    // Kruskal
    for (int i = 1; i <= m; i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];

        if(un(u, v))
        {
            ans += w;
            edgeCnt++;
        }
    }

    if (edgeCnt == n - 1)
    {
        cout << ans << '\n';
    }
    else
    {
        cout << "orz\n";
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