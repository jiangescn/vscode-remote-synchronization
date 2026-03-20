#include <bits/stdc++.h>
using namespace std;
// #define int long long
const int N = 24 * 60 * 60;

void solve()
{
    int n;
    scanf("%d", &n);
    vector<int> s(N + 10);
    for (int i = 1; i <= n; i++)
    {
        int a, b, c;
        scanf("%d:%d:%d", &a, &b, &c);
        int time = a * 3600 + b * 60 + c;
        s[time]++;

        scanf("%d:%d:%d", &a, &b, &c);
        time = a * 3600 + b * 60 + c;
        s[time+1]--;
    }
    int ans = 0;
    for (int i = 1; i <= N; i++)
    {
        s[i] = s[i-1] + s[i];
        ans = max(ans, s[i]);
    }
    printf("%d", ans);
    
}

signed main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}