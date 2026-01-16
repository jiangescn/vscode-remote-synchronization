#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n);
    int count = 0;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
        if(s[i])count++;
        sum += s[i];
    }

    sort(s.rbegin(), s.rend());
    int ans = min(count, sum - n + 1);

    cout << ans << endl;
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