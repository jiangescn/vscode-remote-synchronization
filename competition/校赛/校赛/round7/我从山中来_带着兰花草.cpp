#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;

    int t = 1;
    int count = 0;
    while (n)
    {
        n /= 10;
        count++;
    }

    for (int i = 1; i <= count; i++)
    {
        t *= 10;
    }

    cout << t + 1 << endl;
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