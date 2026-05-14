#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> s(n + 1);
    for (int i = 1; i <= n ; i++)
    {
        cin >> s[i];
    }

    int l = 0;
    for (int i = 1; i <= n; i++)
    {
        if(s[i])
        {
            l = i;
            break;
        }
    }

    int r = 0;
    for (int i = n; i >= 1; i--)
    {
        if(s[i])
        {
            r = i;
            break;
        }
    }

    if(r - l + 1 <= k)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
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