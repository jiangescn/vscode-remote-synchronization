#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2E5 + 10;
int pre[N];

void solve()
{
    int n, k;
    cin >> n >> k;
    pre[0] = 0;
    vector<int> a(n + 1), b(n + 1);

    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    if(k & 1)
    {
        int ans = LLONG_MIN, mn = 0, mx = LLONG_MIN;
        for (int i = 1; i <= n; i++)
        {
            pre[i] = pre[i-1] +a[i];
            mx = max(mx, b[i] - mn);
            ans = max(ans, pre[i] + mx);
            mn = min(mn, pre[i]);
        }
        cout << ans << '\n';
    }
    else
    {
        int sum = a[1], ans = a[1];
        for (int i = 1; i <= n; i++)
        {
            if (i == 1) sum = a[i];
            else sum = max(a[i], sum + a[i]);
            ans = max(ans, sum);
        }
        cout << ans << '\n';
    }

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