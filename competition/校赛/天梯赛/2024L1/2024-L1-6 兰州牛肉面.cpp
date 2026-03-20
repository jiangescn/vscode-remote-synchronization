#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<double> price(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> price[i];
    }

    vector<int> count(n + 1);
    double sum = 0;
    int a, b;
    cin >> a >> b;
    while(a != 0)
    {
        count[a] += b;
        sum += b * price[a];
        cin >> a >> b;
    }

    for (int i = 1; i <= n; i++)
    {
        cout << count[i] << endl;
    }
    cout << fixed << setprecision(2) << sum << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}