#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, h;
    cin >> n >> h;
    vector<int> s(n + 10);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    auto check = [&](int x) -> bool
    {
        int res = h;
        vector<int> ss(x + 1);
        for (int i = 1; i <= x; i++)
        {
            ss[i] = s[i];
        }
        sort(ss.begin() + 1, ss.end());

        int ans1 = 0;
        for (int i = 2; i <= x; i += 2)
        {
            ans1 += ss[i];
        }
        ans1 += ss[x] * (x & 1);
        

        int ans2 = 0;
        for (int i = 1; i <= x; i += 2)
        {
            ans2 += ss[i];
        }
        ans2 += ss[x] * (x % 2 == 0);


        return ((ans1 <= h) || (ans2 <= h));
    };

    int l = 1, r = n;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (check(mid))
        {
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }

    cout << r << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _ = 1;
    // cin >> _;
    while (_--)
    {
        solve();
    }
    return 0;
}