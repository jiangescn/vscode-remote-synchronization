#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s;
    map<int, int> v;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        v[a]++;
        if (v[a] == 1)
        {
            s.push_back(a);
        }
    }
    sort(s.begin(), s.end());
    // for (int i = 0; i < s.size(); i++)
    // {
    //     cout << s[i] << " ";
    // }
    // cout << endl;
    int count = 1;
    int ans = 0;
    for (int i = 1; i < s.size(); i++)
    {
        if (s[i] == s[i - 1] + 1)
        {
            count++;
            ans = max(ans, count);
        }
        else
        {
            count = 1;
        }
    }
    cout << max(ans, 1LL) << endl;
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