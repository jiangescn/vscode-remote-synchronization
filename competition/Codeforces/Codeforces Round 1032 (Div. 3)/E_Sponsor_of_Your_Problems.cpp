#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    string s1, s2;
    cin >> s1 >> s2;

    int ans = 0;
    int n = s1.size();

    int a = 0;
    int b = 0;

    for (int i = 0; i < n; i++)
    {
        a = a * 10 + s1[i] - '0';
        b = b * 10 + s2[i] - '0';

        if (a == b)
        {
            ans += 2;
        }
        else if (b - a == 1)
        {
            ans += 1;
        }
        else
        {
            break;
        }
    }
    cout << ans << endl;
    return;
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