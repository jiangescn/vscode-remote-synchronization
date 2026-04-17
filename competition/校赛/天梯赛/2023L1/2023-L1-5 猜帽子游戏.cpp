#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> tar(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> tar[i];
    }

    int q;
    cin >> q;
    while (q--)
    {
        vector<int> s(n + 1);
        for (int i = 1; i <= n; i++)
        {
            cin >> s[i];
        }

        int full = 1;
        for (int i = 1; i <= n; i++)
        {
            if (s[i] != 0) full = 0;
        }
        if (full)
        {
            cout << "Ai Ya" << endl;
            continue;
        }

        int ok = 1;
        for (int i = 1; i <= n; i++)
        {
            if (s[i] == 0) continue;
            if (s[i] != tar[i])
            {
                ok = 0;
            }
        }
        cout << (ok ? "Da Jiang!!!" : "Ai Ya") << endl;
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