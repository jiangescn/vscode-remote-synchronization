#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n);
    int ji = 0, ou = 0;
    for (int i = 0;i < n; i++)
    {
        cin >> s[i];
        if(s[i] & 1ll)
        {
            ji++;
        }
        else
        {
            ou++;
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        ans += s[i] * (n - 1);
    }
    cout << (ans - ji * ou) / 2 << endl;
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