#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    map<int, int> s;
    for (int i = 1; i <= 10000; i++)
    {
        s[i*i]++;
    }


    int x, l, r;
    cin >> x >> l >> r;

    if(x >= l && x <= r)
    {
        cout << x << endl;
        return;
    }
    for (int i = l; i <= r; i++)
    {
        if(s[x * i])
        {
            cout << i << endl;
            return;
        }
    }

    cout << -1 << endl;
    return;
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