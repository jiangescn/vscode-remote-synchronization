#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int q;
    cin >> q;
    int n;
    cin >> n;

    int count = 0;
    while(q--)
    {
        int a, b, x, y;
        cin >> a >> b >> x >> y;

        if(x == y && a == b)
        {
            count++;
        }
        if(n - x == y && a == -b)
        {
            count++;
        }
    }
    cout << count << endl;
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