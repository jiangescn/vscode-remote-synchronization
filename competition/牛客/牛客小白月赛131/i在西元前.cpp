#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i] >> b[i];
    }

    int tara = a[1] * a[2] + b[1] * b[2];
    int tarb = a[1] * b[2] - a[2] * b[1]; 

    int tarf = a[1] * a[1] + b[1] * b[1];

    int ok = 1;
    for (int i = 3; i <= n; i++)
    {
        int x = i - 1;
        int y = i;
        int cura = a[x] * a[y] + b[x] * b[y];
        int curb = a[x] * b[y] - a[y] * b[x];
        int curf = a[x] * a[x] + b[x] * b[x];

        if (tara * curf != cura * tarf || tarb * curf != curb * tarf)
        {
            cout << "No" << endl;
            return;
        }
    }

    cout << "Yes" << endl;
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