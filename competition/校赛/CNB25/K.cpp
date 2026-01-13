#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int n, k;
    long long p;
    cin >> n >> k >> p;

    unordered_map<int, vector<int>> groups;
    groups.reserve(n * 2);

    for (int i = 0; i < n; ++i)
    {
        long long a;
        cin >> a;
        int r = a % p;
        groups[r].push_back(a);
    }
    int best = LLONG_MAX;

    for (auto &it : groups)
    {
        auto &s = it.second;
        if (s.size() < k)
        {
            continue;
        }

        sort(s.begin(), s.end());
        vector<int> pre(s.size());
        pre[0] = s[0];
        for (int i = 1; i < s.size(); ++i)
            pre[i] = pre[i - 1] + s[i];

        for (int i = k - 1; i < s.size(); ++i)
        {
            int sum = pre[i] - (i - k >= 0 ? pre[i - k] : 0LL);
            int Max = s[i];
            int diff = k * Max - sum;
            int need = diff / p;
            best = min(best, need);
        }
    }

    if (best == LLONG_MAX)
    {
        cout << "wuwuwu" << endl;
    }
    else
    {
        cout << best << endl;
    }
    return 0;
}
