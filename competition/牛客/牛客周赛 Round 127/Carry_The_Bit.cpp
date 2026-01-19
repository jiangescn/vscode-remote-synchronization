#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    string s;
    cin >> s;
    string ans = s;
    int n = s.size();
    int i;
    for (i = 0; i < n; i++)
    {
        if(s[i] >= '5')
        {
            if (i == 0)
            {
                cout << 1;
                break;
            }
            ans[i - 1]++;
            break;
        }
    }
    for (int j = i; j < n; j++)
    {
        ans[j] = '0';
    }
    ans[n - 1] = '0';
    
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