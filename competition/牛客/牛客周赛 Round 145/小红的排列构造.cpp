#include <bits/stdc++.h>
using namespace std;
#define int long long
#define itn int

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);

    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        if (s[i] < 1 || s[i] > n)
        {
            cout << -1 << endl;
            return;
        }
    }
    vector<vector<int>> pos(n + 1);
    for (itn i = 1; i <= n; i++)
    {
        pos[s[i]].push_back(i);

        if (pos[s[i]].size() > 2)
        {
            cout << -1 << endl;
            return;
        }
    }

    if (n & 1)
    {
        cout << -1 << endl;
        return;
    }

    vector<int> vib(n + 1), c(n + 1);
    vector<int> c(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++)
    {
        if(pos[s[i]].size() == 2)
        {
            b[pos[i][0]] = s[i];
            c[pos[i][1]] = s[i];
            b[s[i]]++;
            c[s[i]]++;
        }
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