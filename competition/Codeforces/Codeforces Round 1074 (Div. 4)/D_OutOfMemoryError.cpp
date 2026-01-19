#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m, h;
    cin >> n >> m >> h;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    vector<int> add(n + 1);
    vector<int> las(n + 1, -1);

    int re = 0;

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;

        if(las[a] != re)
        {
            add[a] = 0;
            las[a] = re;
        }

        add[a] += b;

        if(s[a] + add[a] > h)
        {
            re++;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if(las[i] == re)
        {
            cout  << s[i] + add[i] << " ";
        }
        else
        {
            cout << s[i] << " ";
        }
        
    }
    cout << endl;
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