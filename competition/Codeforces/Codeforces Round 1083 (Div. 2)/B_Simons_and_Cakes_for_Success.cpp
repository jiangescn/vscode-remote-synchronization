#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<pair<long long, int>> fct(long long n)
{
    vector<pair<long long, int>> res;
    for (long long i = 2; i * i <= n; i++)
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
    if (n > 1)
        res.push_back({n, 1});
    return res;
}

void solve()
{
    int n;
    cin >> n;

    vector<pair<int, int>> s = fct(n);

    int ans = 1;
    for (int i = 0; i < s.size(); i++)
    {
        ans *= s[i].first;
    }
    cout << ans << endl;
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