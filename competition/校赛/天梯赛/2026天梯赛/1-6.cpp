#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    vector<int> ans;
    for (int i = 1; i <= 11; i++)
    {
        string s;
        getline(cin, s);
        ans.push_back(s.size());
    }

    for (auto it : ans)
    {
        cout << it;
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