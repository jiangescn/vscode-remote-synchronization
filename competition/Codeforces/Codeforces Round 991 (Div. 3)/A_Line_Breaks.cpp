#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> s(1);
    for (int i = 1; i <= n; i++)
    {
        string t;
        cin >> t;
        s.push_back(t.size());
    }

    // sort(s.begin() + 1, s.end());

    int count = 0;
    for (int i = 1; i <= n; i++)
    {
        if (m - s[i] < 0)
            break;
        count++;
        m -= s[i];
    }

    cout << count << endl;
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