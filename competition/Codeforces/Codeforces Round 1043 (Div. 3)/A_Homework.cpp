#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    string a;
    cin >> a;
    int m;
    cin >> m;
    string b, c;
    cin >> b;
    cin >> c;

    for (int i = m - 1; i >= 0; i--)
    {
        if (c[i] == 'V')
            cout << b[i];
    }
    cout << a;
    for (int i = 0; i < m; i++)
    {
        if (c[i] == 'D')
            cout << b[i];
    }
    cout << endl;
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