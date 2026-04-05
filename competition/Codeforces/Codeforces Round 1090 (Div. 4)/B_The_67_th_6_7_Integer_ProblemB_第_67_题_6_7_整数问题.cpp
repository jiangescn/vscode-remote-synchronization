#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    vector<int> s(8);
    int sum = 0;
    for (int i = 1; i <= 7; i++)
    {
        cin >> s[i];
        s[i] *= -1;
        sum += s[i];
    }

    int ans = INT_MIN;
    for (int i = 1; i <= 7; i++)
    {
        ans = max(ans, sum + (s[i] * -2));
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