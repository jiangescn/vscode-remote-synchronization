#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> s(m + 1);
    for (int i = 1; i <= m; i++)
    {
        cin >> s[i];
    }

    sort(s.begin() + 1, s.end());

    if (m == 1)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= 6; j++)
            {
                cout << s[1] << " \n"[j == 6];
            }
        }
        return;
    }

    int l = 1, r = m;
    int op = 1;
    for (int i = 1; i <= n; i++)
    {
        if(op)
        for (int j = 1; j <= 3; j++)
        {
            cout << s[l] << " " << s[r] << " ";
        }
        else
        for (int j = 1; j <= 3; j++)
        {
            cout << s[r] << " " << s[l] << " ";
        }
        cout << endl;

        op ^= 1;

        if(op) l++, r--;
    }
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