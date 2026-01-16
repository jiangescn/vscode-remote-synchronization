// https://ac.nowcoder.com/acm/contest/121302/C

#include <bits/stdc++.h>
using namespace std;
#define MOD 998244353;
#define int long long

int n, ans;
bool vis[20];

vector<vector<int>> s(6);

void dfs(int arr, int dep)
{
    if (dep == n)
    {
        ans++;
        return;
    }

    for (int next : s[arr])
    {
        dfs(next, dep + 1);
    }

    return;
}

signed main()
{
    cin >> n;

    for (int i = 1; i <= 5; i++)
    {
        int x;
        cin >> x;
        for (int t = 0; t < x; t++)
        {
            int a;
            cin >> a;
            s[i].push_back(a);
        }
    }

    for (int i = 1; i <= 5; i++)
    {
        dfs(i, 1);
    }
    cout << ans << endl;
}
