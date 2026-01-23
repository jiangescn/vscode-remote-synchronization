#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> p(n + 1), di(n + 1), d(n + 1);
    map<int, int> vi;
    for (int i = 1; i <= n; i++)
        cin >> p[i];
    for (int i = 1; i <= n; i++)
        cin >> di[i];
    for (int i = 1; i <= n; i++)
        cin >> d[i];


    vector<int> pos(n + 1);
    for (int i = 1; i <= n; i++)
    {
        pos[p[i]] = i;
    }
    for (int i = 1; i <= n; i++)
    {
        int tar = p[di[i]];
        while (!vi[tar])
        {
            vi[tar] = 1;
            tar = d[pos[tar]];
        }
        cout << vi.size() << " ";
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