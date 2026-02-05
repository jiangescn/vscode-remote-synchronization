#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    map<int, int, greater<int>> mp;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        mp[s[i]]++;
    }

    vector<int> ans(n + 1, 0);
    int tar = -1;
    int tareven = -1;
    for (auto it : mp)
    {
        if (it.second % 2 == 1)
        {
            tar = it.first;
            break;
        }
        else
        {  
            if(tareven == -1)tareven = it.first;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (s[i] == tar || s[i] < tareven)
            cout << '1';
        else
            cout << '0';
    }
    cout << '\n';
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