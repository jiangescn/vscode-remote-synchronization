#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int a, b;
    char x, y;
    cin >> a >> x >> b >> y;
    if(a > b)
    {
        cout << "Yes" << endl;
    }
    else if(a < b)
    {
        cout << "No" << endl; 
    }
    else
    {
        if (x < y)
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
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