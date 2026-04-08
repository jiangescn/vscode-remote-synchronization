#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        int a;
        cin >> a;
        sum += a;
    }

    if((sum % 2 != 0) || (n * k % 2 == 0))
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
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