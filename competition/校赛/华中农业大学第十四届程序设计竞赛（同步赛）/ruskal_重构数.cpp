#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    string s;
    cin >> s;
    int n = s.size();
    for (int i = 1; i < n; i++)
    {
        if(s[i - 1] < s[i])
        {
            swap(s[i - 1], s[i]);
            break;
        }
    }

    cout << s << endl;
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