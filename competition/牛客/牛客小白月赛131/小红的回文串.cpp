#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    s = " " + s;

    int mid = n / 2 + (n & 1);
    int ans = 0;

    for (int i = mid; i <= n; i++)
    {
        if(s[i] == s[mid]) ans++;
        else break;
    }

    cout << (ans - 1)* 2 + (n & 1) << endl;
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