#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int s[5][5] = {0};
    int n = 4;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> s[i][j];
        }
    }

    for (int i = 1; i <= n; i++)
    {
        vector<int> va(5);
        for (int j = 1; j <= n; j++)
        {
            va[s[i][j]]++;
            if (va[s[i][j]] > 1)
            {
                cout << "NO" << endl;
                return;
            }
        }
    }
    for (int j = 1; j <= n; j++)
    {
        vector<int> va(5);
        for (int i = 1; i <= n; i++)
        {
            va[s[i][j]]++;
            if (va[s[i][j]] > 1)
            {
                cout << "NO" << endl;
                return;
            }
        }
    }

    vector<int> a(5);
    a[s[1][1]]++, a[s[1][2]]++, a[s[2][1]]++, a[s[2][2]]++;
    for (int i = 1; i <= 4; i++)
    {
        if(a[i] > 1)
        {
            cout << "NO" << endl;
            return;
        }
    }
    vector<int> b(5);
    b[s[3][1]]++, b[s[3][2]]++, b[s[4][1]]++, b[s[4][2]]++;
    for (int i = 1; i <= 4; i++)
    {
        if(b[i] > 1)
        {
            cout << "NO" << endl;
            return;
        }
    }
    vector<int> c(5);
    c[s[1][3]]++, c[s[1][4]]++, c[s[2][3]]++, c[s[2][4]]++;
    for (int i = 1; i <= 4; i++)
    {
        if(c[i] > 1)
        {
            cout << "NO" << endl;
            return;
        }
    }
    vector<int> d(5);
    d[s[3][3]]++, d[s[3][4]]++, d[s[4][3]]++, d[s[4][4]]++;
    for (int i = 1; i <= 4; i++)
    {
        if(d[i] > 1)
        {
            cout << "NO" << endl;
            return;
        }
    }

    cout << "YES" << endl;
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