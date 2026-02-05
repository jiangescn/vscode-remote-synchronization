#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;

vector<string> mm = {
    "1110111", // 0
    "0010010", // 1
    "1011101", // 2
    "1011011", // 3
    "0111010", // 4
    "1101011", // 5
    "1101111", // 6
    "1010010", // 7
    "1111111", // 8
    "1111011"  // 9
};

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
    return r;
}

void solve()
{
    int k;
    cin >> k;

    vector<int> s(7);
    for (int i = 0; i < 7; i++)
    {
        cin >> s[i];
        s[i] = s[i] * qpow(100, mod - 2) % mod;
    }

    vector<int> qp(10);
    for (int mask = 1; mask < (1 << 7); mask++)
    {
        int q = 1;
        for (int j = 0; j < 7; j++)
        {
            if (mask & (1 << j))
            {
                q = q * s[j] % mod;
            }
            else
            {
                q = q * ((1 - s[j] + mod) % mod) % mod;
            }
        }

        for (int d = 0; d <= 9; d++)
        {
            int ok = 1;
            for (int j = 0; j < 7; j++)
            {
                int t = (mask >> j) & 1;
                if (t != mm[d][j] - '0')
                {
                    ok = 0;
                    break;
                }
            }

            if (ok)
            {
                qp[d] = (qp[d] + q) % mod;
            }
        }
    }

    int ans = 0;
    for (int a = 0; a <= 9999; a++)
    {
        int b = k - a;
        if (b < 0 || b > 9999)
        {
            continue;
        }

        int cur = 1;
        int x = a;
        for (int i = 0; i < 4; i++)
        {
            cur = cur * qp[x % 10] % mod;
            x /= 10;
        }

        x = b;
        for (int i = 0; i < 4; i++)
        {
            cur = cur * qp[x % 10] % mod;
            x /= 10;
        }

        ans = (ans + cur) % mod;
    }

    cout << ans << endl;
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