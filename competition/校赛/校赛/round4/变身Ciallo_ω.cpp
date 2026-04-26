#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int m, n;
    cin >> n >> m ;
    string s;
    cin >> s;

    for (int i = 0; i < m; i++)
    {
        s[i] = toupper(s[i]);
    }

    for (int i = m; i < n; i++)
    {
        s[i] = tolower(s[i]);
    }

    cout << s << endl;
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