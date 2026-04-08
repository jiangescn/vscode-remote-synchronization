#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int people, house;
    cin >> people >> house;
    vector<array<int, 2>> a;
    a.reserve(people + 1);
    vector<array<int, 2>> b;
    b.reserve(people + 1);

    int sum = 0;
    for (int i = 0; i < people; i++)
    {
        int x, y;
        cin >> x >> y;
        if (x < y)
        {
            a.push_back({x, y});
            sum += y;
        }
        else
        {
            b.push_back({x, y});
        }
    }

    sort(a.begin(), a.end(), [&](auto &x, auto &y)
         { return x[1] - x[0] < y[1] - y[0]; });

    int want_alone = a.size();
    int max_alone = house - people;

    if (people == 1)
    {
        if (!a.empty())
        {
            cout << a[0][1] << endl;
        }
        else
        {
            cout << b[0][1] << endl;
        }
        return;
    }

    if (want_alone == people && house >= 2 * want_alone - 1) // 所有人都想独居 && 独居的房子足够
    {
        cout << sum << endl;
    }
    else if (max_alone >= want_alone) // 有一部分想独居 && 独居的房子足够
    {
        if (want_alone == people - 1) // 只有一个人不想独居
        {
            cout << max(sum - a[0][1] + a[0][0] + b[0][0], sum + b[0][1]) << endl;
        }
        else //有多人不想独居
        {
            int ans = sum;
            for (int i = 0; i < b.size(); i++)
            {
                ans += b[i][0];
            }
            cout << ans << endl;
        }
    }
    else // 独居的房子不够 (让差值小的人妥协)
    {
        int nm = want_alone - max_alone;
        int ans = sum;
        for (int i = 0; i < nm; i++)
        {
            ans = ans - a[i][1] + a[i][0];
        }

        for (int i = 0; i < b.size(); i++)
        {
            auto [x, y] = b[i];
            ans = ans + x;
        }

        cout << ans << endl;
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int _ = 1;
    cin >> _;
    while (_--)
    {
        solve();
    }
    return 0;
}