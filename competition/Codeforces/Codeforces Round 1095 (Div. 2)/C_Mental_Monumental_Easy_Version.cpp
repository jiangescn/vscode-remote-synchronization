#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;

    vector<int> s(n + 1);
    multiset<int> st;

    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        st.insert(s[i]);
    }

    auto check = [&](int md) -> bool
    {
        multiset<int> temp = st;

        for (int i = md - 1; i >= 0; i--)
        {
            if (temp.count(i))
            {
                temp.erase(temp.find(i));
                continue;
            }

            auto it = temp.lower_bound(2 * i + 1);

            if (it == temp.end())
            {
                return false;
            }

            temp.erase(it);
        }

        return true;
    };

    int l = 0, r = n;

    while (l <= r)
    {
        int mid = l + ((r - l) >> 1);

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
    cin.tie(nullptr), cout.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}