#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    char a, b, c, d;
    cin >> a >> b >> c >> d;
    if(b == c)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }

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