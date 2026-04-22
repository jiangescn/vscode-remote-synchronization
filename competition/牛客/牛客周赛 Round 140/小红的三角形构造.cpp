#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;

    if(n == 1 || n == 2)
    {
        cout << "No" << endl;
        return;
    }
    else if(n & 1)
    {
        cout << "Yes" << endl;
        cout << n << " " << n * n / 2 << " " << n * n / 2 + 1 << endl;
    }
    else
    {
        cout << "Yes" << endl;
        cout << n << " " << n * n / 4 + 1 << " " << n * n / 4 - 1 << endl;
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