#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    string s;
    cin >> s;

    int n = s.size();
    s = " " + s;

    int count = 0;
    for (int i = 1; i <= n; i++)
    {
        if (i != 1 && i != n)
        {
            if (count == 0)
            {
                cout << "YES" << endl;
                return;
            }
        }

        if (s[i] == '(')
        {
            count++;
        }
        else
        {
            count--;
        }

        // cout << count << " ";
    }
    // cout << endl;

    cout << "NO" << endl;
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