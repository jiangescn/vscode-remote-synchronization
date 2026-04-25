#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(1);
    for (int i = 1; i <= n; i++)
    {
        int a;
        cin >> a;
        s.push_back(a);
    }

    sort(s.begin(), s.end());
    s.erase(unique(s.begin(), s.end()), s.end());

    int cur = s[1];

    for (int i = 1; i < s.size(); i++)
    {
        
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