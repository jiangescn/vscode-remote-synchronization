#include <bits/stdc++.h>
using namespace std;
// #define int long long

void solve()
{
    int n;
    cin >> n;
    vector<pair<int, int>> s(n + 1);

    map<int, vector<int>> count;

    for (int i = 1; i <= n; i++)
    {
        cin >> s[i].first;
        count[s[i].first].push_back(i);
        s[i].second = i;
    }

    sort(s.begin() + 1, s.end());

    int Max = 0;
    for (auto it : count)
    {
        Max = max(Max, it.first);
    }

    for (int i = 0; i < count[Max].size(); i++)
    {
        if(i != 0) cout << " ";
        cout << count[Max][i];
    }
    cout << endl;


    vector<int> ss(n);
    for (int i = 1; i <= n; i++)
    {
        ss[i - 1] = s[i].first;
    }

    int q;
    cin >> q;
    while(q--)
    {
        int x;
        cin >> x;

        int found = 0;

        auto tpos = upper_bound(ss.begin(), ss.end(), x);

        if(tpos == ss.end())
        {
            cout << 0 << endl;
        }
        else
        {
            int pos = tpos - ss.begin();

            cout << s[pos + 1].second << endl;
        }

    }
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