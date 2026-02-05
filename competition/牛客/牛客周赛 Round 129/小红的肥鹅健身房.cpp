#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;

    map<int, int> s;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int a;
            cin >> a;
            s[a]++;
        }
    }

    int count = 0;
    int coin = 0;
    for (auto it : s)
    {
        if(it.first == 0 || it.second < 2)
        {
            continue;
        }
        s[it.first + 1] += it.second / 2;
        count += it.second / 2;
        if(it.first + 1 >= k)
        {
            coin += it.second / 2;
        }
    }

    cout << count << " " << coin << endl;

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