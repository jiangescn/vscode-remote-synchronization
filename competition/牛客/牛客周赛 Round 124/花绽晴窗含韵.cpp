#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int a, b;
    cin >> a >> b;
    if(a == b)
    {
        cout << "Draw" << endl;
    }
    else if(a > b)
    {
        cout << "Alice" << endl;
    }
    else
    {
        cout << "Bob" << endl;
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