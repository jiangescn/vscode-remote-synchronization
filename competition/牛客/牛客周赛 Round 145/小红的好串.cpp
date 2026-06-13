#include <bits/stdc++.h>
using namespace std;
#define int long long
#define itn int

void solve()
{

    char s, b, c;
    cin >> s >> b >> c;

    if(s == b && b == c || s != b && b != c && s != c)
    {
        cout << "No" << endl;
    }
    else
    {
        cout << "Yes" << endl;
    }

}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}