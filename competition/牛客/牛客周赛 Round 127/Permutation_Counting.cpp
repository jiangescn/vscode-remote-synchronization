#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 10;
const int mod = 998244353;

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
    vector<int> s(n);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
    }
    
    vector<int> da(N);
    for (int i = 0; i < n; i++)
    {
        if(s[i] <= n)
        {
            da[s[i]]++;
        }
    }

    int ans = 0;
    int las = 1;
    for (int i = 1; i <= n; i++)
    {
        if(da[i] < 2)
        {
            break;
        }
        int c = (da[i] * (da[i] - 1)) % mod;
        c = c * ksm(2, mod - 2, mod) % mod;

        las = las * c % mod;

        ans += las;
        ans %= mod;

    }
    cout << ans % mod << '\n';
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