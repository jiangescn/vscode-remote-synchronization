#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<pair<long long, int>> fct(int n)
{
    vector<pair<long long, int>> res;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            int cnt = 0;
            while (n % i == 0)
            {
                n /= i;
                cnt++;
            }
            res.push_back({i, cnt});
        }
    }
    if (n > 1) res.push_back({n, 1});
    return res;
}

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    int countodd = 0;
    int counteven = 0;
    map<int, int> count;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        vector<pair<long long, int>> t = fct(s[i]);
        for (auto [a, b] : t)
        {
            count[a]++;
        }
    }
    for (int i = 1; i <= n; i++) cin >> s[0];

    int cnt1 = 0;
    int cnt2 = 0;
    for (auto it : count)
    {
        if(it.first == 1) continue;
        if(it.second >= 2) cnt2++;
        if(it.second >= 1) cnt1++;
    }
  
    // cout << "count1:" << cnt1 << "  count2:" << cnt2 << endl;

    if(cnt2)
    {
        cout << 0 << endl;
        return;
    }

    // 枚举每个 ai，看 ai + 1 的质因子是否在原数组中出现过
    for (int i = 1; i <= n; i++)
    {
        vector<pair<long long, int>> t = fct(s[i] + 1);

        for (auto [a, b] : t)
        {
            if (count[a] >= 1)
            {
                cout << 1 << endl;
                return;
            }
        }
    }

    cout << 2 << endl;
    return;
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