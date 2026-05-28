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

    sort(s.begin(), s.end());

    int l = -1, r = -1;
    for (int i = 1; i <= n; i++)
    {
        if(s[i] & 1)
        {
            l = i;
            break;
        }
    }

    for (int i = n; i >= 1; i--)
    {
        if(s[i] & 1)
        {
            r = i;
            break;
        }
    }

    int ans = INT_MAX;

    if(l != -1 && r != -1) 
    ans = l - 1 + n - r;

    l = -1, r = -1;
    for (int i = 1; i <= n; i++)
    {
        if (s[i] % 2 == 0)
        {
            l = i;
            break;
        }
    }

    for (int i = n; i >= 1; i--)
    {
        if (s[i] % 2 == 0)
        {
            r = i;
            break;
        }
    }

    
    if(l != -1 && r != -1) 
    ans = min(ans, l - 1 + n - r);

    cout << ans << endl;
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