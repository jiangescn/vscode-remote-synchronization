#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    string s;
    cin >> s;
    int n = s.size();

    int ans = 0;
    int i = 0;

    for (int i = 0; i < n; i++)
    {
        if(i == 0 && s[i] == 'u')
        {
            ans++;
            s[i] = 's';
        }
        else if(i == n - 1 && s[i] == 'u')
        {
            ans++;
        }
        else
        {
            if(s[i] == 'u')
            {
                if(s[i + 1] == 'u')
                {
                    ans++;
                    s[i + 1] = 's';
                }
            }
        }
    }
    

    cout << ans << '\n';
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