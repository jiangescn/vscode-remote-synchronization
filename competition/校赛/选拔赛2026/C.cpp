#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    int fir = s[1];
    // cout << "fir:" << fir << endl;
    s[0] = s[1];

    int bk = s[n];

    int last = s[1];

    int i;

    for (i = 1; i <= n; i++)
    {
        if (s[i] >= last)
        {
            last = s[i];
            cout << '1';
        }
        else if (s[i] <= fir)
        {
            bk = s[i];
            break;
        }
        else
        {
            cout << 0;
        }
    }

    // cout << "bk:" << bk << endl;
    // cout << "pos:" << pos << endl;

    for (i; i <= n; i++)
    {
        // cout << "pos: " << pos << "  bk:" << bk << endl;
        if ((s[i] <= fir) && (s[i] >= bk))
        {
            cout << '1';
            bk = s[i];
        }
        else
        {
            cout << '0';
        }
    }

    cout << '\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--)
    {
        solve();
    }
    return 0;
}