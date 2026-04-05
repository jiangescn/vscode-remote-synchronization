#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    int x = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        x ^= s[i];
    }

    int pre_count = 0;
    int ans = 0;
    int pre = 0, suf = (x ^ s[1]);
    for (int i = 2; i <= n - 1; i++)
    {
        pre ^= s[i -1];
        suf ^= s[i];
        if(pre == x)
        {
            pre_count++;
        }

        if(suf == x)
        {
            ans += pre_count;
        }
    }


    cout << ans << endl;
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