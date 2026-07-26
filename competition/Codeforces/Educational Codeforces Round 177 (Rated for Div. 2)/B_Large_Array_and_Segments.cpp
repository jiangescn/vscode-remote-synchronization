// Problem URL: https://codeforces.com/contest/2086/problem/B
// Problem Name: B. Large Array and Segments
#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k ,x;
    cin >> n >> k >> x;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    vector<int> pre(n + 1);
    for (int i = 1; i <= n; i++)
    {
        pre[i] = pre[i - 1] + s[i];
    }

    int sum = pre[n] * k;
    if(sum < x)
    {
        cout << 0 << endl;
        return;
    }

    int ans = 0;

    for (int i = 1; i <= n; i++)
    {
        if(pre[i - 1] > sum - x)
        {
            continue;
        }

        int Max = (sum - x - pre[i - 1]) / pre[n];

        int count = min(k - 1, Max) + 1;

        ans += count;
    }

    cout << ans << endl;

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