#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> threepow(21);

void solve()
{
    int n;
    cin >> n;

    int ans = 0;
    for (int i = 19; i >= 0; i--)
    {
        if(n >= threepow[i])
        {
            ans += (threepow[i + 1] + i * threepow[i - 1]) * (n / threepow[i]);
        }
        n %= threepow[i];
    }
    cout << ans << endl;
    return;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    threepow[0] = 1;
    for (int i = 1; i <= 19; i++)
    {
        threepow[i] = threepow[i - 1] * 3;
    }
    
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}