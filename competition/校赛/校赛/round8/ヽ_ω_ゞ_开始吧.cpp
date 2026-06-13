#include <bits/stdc++.h>
using namespace std;
#define int long long
#define itn int

void solve()
{
    string s;
    cin >> s;

    int n = s.size();
    s = " " + s;

    int ans = 0;
    int cha = 99999;

    for (int i = 1; i <= n - 2; i++)
    {
        string temp = s.substr(i, 3);
        int t = stoll(temp);

        if (abs(t - 753) < cha)
        {
            cha = abs(t - 753);
            ans = t;
        }
    }

    cout << cha << endl;
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