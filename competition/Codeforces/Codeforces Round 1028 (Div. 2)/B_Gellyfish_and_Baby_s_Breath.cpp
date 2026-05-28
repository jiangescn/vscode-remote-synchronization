#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;

int qpow(int a, int b)
{
    int r = 1;
    while (b)
    {
        if (b & 1)
            r = r * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return r % mod;
}

void solve()
{
    int n;
    cin >> n;

    vector<int> p(n + 1), q(n + 1);
    vector<int> posp(n), posq(n);

    for (int i = 1; i <= n; i++)
    {
        cin >> p[i];
        posp[p[i]] = i;
    }

    for (int i = 1; i <= n; i++)
    {
        cin >> q[i];
        posq[q[i]] = i;
    }

    int mxp = -1, mxq = -1;

    for (int i = 1; i <= n; i++)
    {
        mxp = max(mxp, p[i]);
        mxq = max(mxq, q[i]);

        int mx = max(mxp, mxq);
        int other = -1;

        if (posp[mx] <= i)
        {
            int j = posp[mx];
            other = max(other, q[i - j + 1]);
        }

        if (posq[mx] <= i)
        {
            int j = posq[mx];
            other = max(other, p[i - j + 1]);
        }

        int ans = (qpow(2, mx) + qpow(2, other)) % mod;
        cout << ans << " ";
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