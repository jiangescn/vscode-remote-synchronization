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
        char c;
        cin >> c;
        s[i] = c - '0';
    }

    // for (int i = 1; i <= n; i++)
    // {
    //     cout << s[i] << " \n"[i == n];
    // }

    map<array<int, 3>, int> mp;
    int a = 0, b = 0, c = 0;
    for (int i = 1; i <= n; i++)
    {
        if (s[i] == 0) a++;
        if (s[i] == 1) b++;
        if (s[i] == 2) c++;

        int t = min({a, b, c});
        a -= t, b -= t, c -= t;

        mp[{a, b, c}]++;
    }

    if (mp[{0, 0, 0}]) mp[{0, 0, 0}]++;

    int ans = 0;
    for (auto it : mp)
    {
        // cout << it.first[0] << " " << it.first[1] << " " << it.first[2] << "  :" << it.second << endl;
        int temp = it.second - 1;
        ans += (temp + 1) * temp / 2;
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