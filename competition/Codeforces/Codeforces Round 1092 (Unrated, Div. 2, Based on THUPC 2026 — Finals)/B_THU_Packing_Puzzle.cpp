#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int a, b, c;
    cin >> a >> b >> c;

    int ans = 0;
    int Min = min(a, c);
    ans += Min * 4;
    a -= Min, c -= Min;

    if(a == 0)
    {
        ans += b * 3 + c * 3;
        cout << ans << endl;
        return;
    }
    
    Min = min(a / 2, b);
    ans += Min * 7;
    a -= Min * 2, b -= Min;

    if (a == 0)
    {
        ans += b * 3 + c * 3;
        cout << ans << endl;
        return;
    }

    Min = min(a, b);
    ans += Min * 5;
    a -= Min, b -= Min;

    if (a == 0)
    {
        ans += b * 3 + c * 3;
        cout << ans << endl;
        return;
    }

    ans += (a-- >= 1) * 3;
    ans += max(a, 0ll) * 2;
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