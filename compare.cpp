#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int a = 1, b = 1, c = 0;
    int n;
    cin >> n;
    for (int i = 3; i <= n; i++)
    {
        c = a + b;
        a = b;
        b = c;
    }
    cout << c << ".00";
    return;
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