#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int x1, y1;
    int x2, y2;
    cin >> x1 >> y1;
    cin >> x2 >> y2;

    if(y1 == y2)
    {
        double mianji = abs(x1 - x2) * abs(y1) / 2.0;
        if(abs(mianji - 2.0) <= 0.001)
        {
            cout << 0 << endl;
        }
        else
        {
            cout << "no answer" << endl;
        }
        return;
    }

    int t = x1 * y2 - x2 * y1;

    double x = (4.0 - t) / double(y2 - y1);
    cout << fixed << setprecision(10) << -x << endl;


}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}