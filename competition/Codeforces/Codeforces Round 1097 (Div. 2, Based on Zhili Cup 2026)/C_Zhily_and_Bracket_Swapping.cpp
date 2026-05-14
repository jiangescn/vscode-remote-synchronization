#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    string s1, s2;
    cin >> s1 >> s2;

    s1 = " " + s1;
    s2 = " " + s2;

    int base = 0, mix = 0;

    for (int i = 1; i <= n; i++)
    {
        if (s1[i] == s2[i])
        {
            if (s1[i] == '(')
                base++;
            else
                base--;
        }
        else
        {
            mix++;
        }

        if (base < mix % 2)
        {
            cout << "NO" << endl;
            return;
        }
    }

    if (base == 0 && mix % 2 == 0)
        cout << "YES" << endl;
    else
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