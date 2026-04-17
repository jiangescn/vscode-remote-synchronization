#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int a, b, c;
    cin >> a >> b >> c;
    
    if(a + b == c)
    {
        cout << "Tu Dou" << endl;
    }
    else if(a * b == c)
    {
        cout << "Lv Yan" << endl;
    }
    else
    {
        cout << "zhe du shi sha ya!" << endl;
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