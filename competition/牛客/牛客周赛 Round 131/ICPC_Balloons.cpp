#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    char c;
    cin >> c;
    switch (c)
    {
    case 'A':
        cout << "red" << endl; break;
    case 'B':
        cout << "orange" << endl;
        break;
    case 'C':
        cout << "blue" << endl;
        break;
    case 'D':
        cout << "green" << endl;
        break;

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