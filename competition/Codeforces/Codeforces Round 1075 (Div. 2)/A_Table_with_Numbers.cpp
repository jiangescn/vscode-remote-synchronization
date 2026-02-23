#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, h, l;
    cin >> n >> h >> l;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    int mn = min(h, l);
    int mx = max(h, l);
    int countmn = 0;
    int countmx = 0;
    for (int i = 1; i <= n; i++)
    {
        if(s[i] <= mn)
        {
            countmn++;
        }
        if(s[i] <= mx)
        {
            countmx++;
        }
    }

    cout << min(countmn, countmx / 2) << endl;
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