#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int x1, y1;
    int x2, y2;
    int x3, y3;
    cin >> x1 >> y1;
    cin >> x2 >> y2;
    cin >> x3 >> y3;

    if(x1 == x2 && x2 == x3)
    {
        swap(x1, y1);
        swap(x2, y2);
        swap(x3, y3);
    }
    

    int Max = max({x1, x2, x3});
    int Min = min({x1, x2, x3});
    int tar = x1 + x2 + x3 - Max - Min;
    if(x1 == tar)
    {
        cout << 1 << endl;
    }
    else if(x2 == tar)
    {
        cout << 2 << endl;
    }
    else
    {
        cout << 3 << endl;
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