#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int a, b;
    cin >> a >> b;
    if(b != 3 && b != 0 && b != 6 && b != 9)
    {
        cout << b << " " << 9 << endl;
    }
    else if(b == 3)
    {
        cout << 1 << " " << 3 << endl;
    }
    else if(b == 6)
    {
        cout << 2 << " " << 3 << endl;
    }
    else if(b == 0)
    {
        if(a == 1)
        {
            cout << 1 << " " << 100 << endl;
        }
        else
        {
            cout << 1 << " " << 10 << endl;
        }
    }
    else
    {
        if (a % 2)
        {
            cout << 10 << " " << 11 << endl;
        }
        else
        {
            cout << 1 << " " << 11 << endl;
        }
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