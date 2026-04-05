#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    vector<int> s(3);
    cin >> s[0] >> s[1] >> s[2];
    sort(s.begin(), s.end());

    if(s[0] != s[1])
    {
        cout << s[1] << " " << s[0] << " " << s[2] << endl;
    }
    else
    {
        cout << -1 << endl;
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