#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, x;
    cin >> n >> x;

    int fir = 0;
    int once = 0;

    for (int i = 0; i < n; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;

        fir += a * (b - 1);
        int temp = a * b - c;
        once = max(once, temp);
    }

    if (fir >= x)
    {
        cout << 0 << endl;
        return;
    }

    int need = x - fir;
    if (once <= 0)
    {
        cout << -1 << endl;
        return;
    }

    int ans = (need + once - 1) / once;
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