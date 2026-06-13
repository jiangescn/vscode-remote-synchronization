#include <bits/stdc++.h>
using namespace std;
// #define int long long
// #define itn int

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    auto check = [&](int x)
    {
        unordered_map<int, int> mp;
        int count = 0;
        int ans = 0;
        for (int i = 1; i <= n; i++)
        {
            if(s[i] < x && !mp[s[i]])
            {
                mp[s[i]] = 1;
                count++;
            }

            if(count >= x)
            {
                ans++;
                count = 0;
                for (auto &it : mp) it.second = 0; 
            }
        }
        return ans >= k;
    };

    int l = 0, r = n;
    while(l <= r)
    {
        int mid = (l + r) >> 1;
        
        if(check(mid))
        {
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }

    cout << r << '\n';
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