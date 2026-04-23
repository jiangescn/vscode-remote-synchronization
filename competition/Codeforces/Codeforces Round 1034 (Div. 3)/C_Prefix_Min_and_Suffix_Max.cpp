#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    vector<int> premin(n + 1);
    vector<int> demax(n + 2);
    premin[0] = s[1];
    for (int i = 1; i <= n; i++)
    {
        premin[i] = min(s[i], premin[i - 1]);
    }
    for (int i = n; i >= 1; i--)
    {
        demax[i] = max(s[i], demax[i + 1]);
    }

    for (int i = 1; i <= n; i++)
    {
        if(s[i] <= premin[i] || s[i] >= demax[i])
        {
            cout << 1;
        }
        else
        {
            cout << 0;
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