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
        cin >> s[i];
    }

    sort(s.begin() + 1, s.end());

    vector<int> ans;

    for (int i = 1; i <= n; i++)
    {
        if (ans.empty())
        {
            ans.push_back(s[i]);
            continue;
        }

        if(s[i] - ans.back() >= ans.size())
        {
            ans.push_back(s[i]);
        }
    }

    cout << ans.size() << endl;
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