#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    int x = min(a, c);
    int y = min(b, d);

    if(x >= y)
    {
        cout << "Gellyfish" << endl;
    }
    else
    {
        cout << "Flower" << endl;
    } 

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