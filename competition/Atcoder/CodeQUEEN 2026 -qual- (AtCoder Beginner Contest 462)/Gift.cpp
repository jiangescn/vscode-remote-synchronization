#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        int k;
        cin >> k;
        for (int j = 1; j <= k; j++)
        {
            int a;
            cin >> a;
            s[a].push_back(i);
        }
    }


    for (int i = 1; i <= n; i++)
    {
        cout << s[i].size() << " ";
        for (auto it : s[i])
        {
            cout << it << " ";
        }
        cout << endl;
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