// Problem URL: https://codeforces.com/contest/2086/problem/C
// Problem Name: C. Disappearing Permutation
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
    vector<int> d(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> d[i];
    }

    vector<int> vi(n + 1);
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int tar = d[i];
        while(!vi[s[tar]])
        {
            vi[s[tar]] = 1;
            tar = s[tar];
            ans++;
        }
        cout << ans << " ";
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