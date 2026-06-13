#include <bits/stdc++.h>
using namespace std;
#define int long long
#define itn int

void solve()
{
    string s;
    cin >> s;

    int n = s.size();

    int ans = 0;
    int fir = 0;

    for (int i = n - 1; i >= 0; i--)
    {
        if(s[i] == '0' && fir) continue;
        ans++;
        if(s[i] != '0') fir = 1;
    }

    cout << ans - 1 << endl;

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