#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <string>
using namespace std;
#define int long long
const int mod = 998244353;
const int N = 2e6 + 10;

int ksm(int a, int b)
{
    int r = 1;
    while(b)
    {
        if(b & 1)
        {
            r = r * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return r;
}

void solve()
{
    vector<int> s(N);
    s[1] = 0;
    s[2] = 1;
    for (int i = 3; i < N; i++)
    {
        s[i] = (i - 1) * (s[i- 1] + s[i - 2]) % mod;
    }

    // for (int i = 1; i <= 10; i++)
    // {
    //     cout << s[i] << " ";
    // }cout << endl;

    int q;
    cin >> q;
    while(q--)
    {
        int a;
        cin >> a;
        int d = ksm(a - 1, a);
        cout << s[a] * ksm(d, mod - 2) % mod << endl;
    }

}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}