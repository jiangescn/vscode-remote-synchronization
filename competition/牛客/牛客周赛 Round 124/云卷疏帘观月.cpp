#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1E9 + 7;

int ksm(int a, int b, int mod)
{
    int ans = 1;
    while (b)
    {
        if (b & 1)
        {
            ans = ans * a % mod;
        }
        a = a * a % mod;
        b /= 2;
    }
    return ans % mod;
}

void solve()
{
    int n;
    cin >> n;
    cout << ksm(2, n / 2, N) << endl;
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