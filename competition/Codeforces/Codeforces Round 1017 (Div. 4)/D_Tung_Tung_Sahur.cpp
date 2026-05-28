#include <bits/stdc++.h>
using namespace std;

void solve()
{
    string p, s;
    cin >> p >> s;

    int n = p.size(), m = s.size();
    int i = 0, j = 0;

    while (i < n && j < m)
    {
        if (p[i] != s[j])
        {
            cout << "NO\n";
            return;
        }

        char c = p[i];

        int cnt1 = 0;
        while (i < n && p[i] == c)
        {
            cnt1++;
            i++;
        }

        int cnt2 = 0;
        while (j < m && s[j] == c)
        {
            cnt2++;
            j++;
        }

        if (cnt2 < cnt1 || cnt2 > 2 * cnt1)
        {
            cout << "NO\n";
            return;
        }
    }

    if (i == n && j == m)
        cout << "YES\n";
    else
        cout << "NO\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}