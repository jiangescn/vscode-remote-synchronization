#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n);
    map<int, int> count;
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
        count[i]++;
    }

    int ans = 0;
    for (auto it : count)
    {
        if(it.second  >= 2)
        {
            ans += it.second - 1;
            count[it.first + 1] += it.second - 1;
            it.second = 1;
        }
    }

    cout << ans << endl;

}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}