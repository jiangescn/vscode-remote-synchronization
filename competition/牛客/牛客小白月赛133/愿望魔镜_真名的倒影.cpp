#include <bits/stdc++.h>
using namespace std;
#define int long long
#define itn int

void solve()
{
    string s;
    cin >> s;

    if (s == "awdec")
    {
        cout << "Fantasy_Blue" << endl;
    }
    else if (s == "Fantasy_Blue")
    {
        cout << "awdec" << endl;
    }
    else
    {
        cout << "other" << endl;
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