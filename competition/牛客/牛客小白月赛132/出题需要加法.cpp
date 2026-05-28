#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> s;

void solve()
{
    int l, r;
    cin >> l >> r;

    // for (int i = 0; i < s.size(); i++)
    // {
    //     cout << s[i] << " ";
    // }

    auto L = lower_bound(s.begin(), s.end(), l);
    auto R = upper_bound(s.begin(), s.end(), r);

    cout << R - L << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    for (int i = 0; i <= 62; i++)
    {
        for (int j = 0; j <= 61; j++)
        {
            s.push_back((1ll << i) + (1ll << j));
        }
    }

    sort(s.begin(), s.end());
    s.erase(unique(s.begin(), s.end()), s.end());

    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}