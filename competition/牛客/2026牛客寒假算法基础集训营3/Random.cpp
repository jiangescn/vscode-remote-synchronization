#include <bits/stdc++.h>
using namespace std;
// #define int long long

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

    for (int i = 1; i < n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            if(__gcd(s[i], s[j]) > 1)
            {
                cout << s[i] << " " << s[j] << endl;
                return;
            }
        }
    }

    cout << -1 << endl;
    return;
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