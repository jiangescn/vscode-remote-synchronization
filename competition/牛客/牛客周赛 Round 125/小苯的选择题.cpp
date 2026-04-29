#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    string s;
    cin >> s;

    if(s.find('C') != -1)
    {
        cout << 0 << endl;
        return;
    }

    if(s == "ABD")
    {
        cout << 4 << endl;
        return;
    }

    cout << 2 << endl;
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