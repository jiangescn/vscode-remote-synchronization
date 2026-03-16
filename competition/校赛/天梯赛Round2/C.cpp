#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int x, y, z;
    cin >> x >> y >> z;
    int once = 3 * x + y;
    int time = z / once;
    int yuxia = z % once;

    // cout << "yuxia:" << yuxia << endl;

    int need = 0;
    if (yuxia == 0)
    {
        cout << time * 3 << endl;
        return;
    }
    else if (yuxia <= (x + y))
    {
        need = 1;
    }
    else if (yuxia <= (2 * x + y))
    {
        need = 2;
    }
    else
    {
        need = 3;
    }

    cout << time * 3 + need << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int _ = 1;
    while (_--)
    {
        solve();
    }
    return 0;
}