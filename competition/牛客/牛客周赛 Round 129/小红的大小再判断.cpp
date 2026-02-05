#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    string s;
    cin >> s;
    string re = s;
    for (int i = 0; i < s.size(); i++)
    {
        re[i] = s[s.size() - 1 - i];
    }

    // cout << "re:" << re << endl;

    if (s > re)
    {
        cout << "left" << endl;
    }
    else if (s < re)
    {
        cout << "right" << endl;
    }
    else
    {
        cout << "equal" << endl;
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