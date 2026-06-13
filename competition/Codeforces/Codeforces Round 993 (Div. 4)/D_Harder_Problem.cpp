#include <bits/stdc++.h>
using namespace std;
#define int long long
#define itn int

void solve()
{
    itn n;
    cin >> n;
    
    vector<int> s(n + 1);
    map<int, int> vi;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    vector<int> ans(n + 1);
    for (int i = 1; i <= n; i++)
    {
        if(!vi[s[i]])
        {
            ans[i] = s[i];
            vi[s[i]] = 1;
        }
    }

    int idx = 1;
    for (itn i = 1; i <= n; i++)
    {
        if(ans[i]) continue;
        while(vi[idx])
        {
            idx++;
        }
        ans[i] = idx;
        vi[idx] = 1;
    }

    for (int i = 1; i <= n; i++)
    {
        cout << ans[i] << " \n"[i == n];
    }
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