#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int w, h, a, b;
    cin >> w >> h >> a >> b;

    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    int dx = abs(x1 - x2);
    int dy = abs(y1 - y2);

    // cout << dx << " " << dy << endl;

    if (dx && dx % a == 0 || dy && dy % b == 0)
    {
        cout << "Yes" << endl;
        return;
    }

    if (dx == 0 && dy == 0)
    {
        cout << "Yes" << endl;
        return;
    }

    cout << "No" << endl;
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