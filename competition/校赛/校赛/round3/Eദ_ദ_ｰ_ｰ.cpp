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


    vector<int> candi;
    int l = 1, r = 2;
    while(l <= n && r <= n)
    {
        if(s[r] < s[l])
        {
            candi.push_back(s[l] - s[r]);
            r++;
        }
        else
        {
            l = r;
            r++;
        }
    }

    sort(candi.begin(), candi.end());
    int m = candi.size();

    int ans = 0;
    int plus = 0;

    for (int i = 0; i < m; i++)
    {
        if(candi[i] - plus == 0) continue;
        ans += (candi[i] - plus) * (m - i + 1);
        plus = candi[i];
    }

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