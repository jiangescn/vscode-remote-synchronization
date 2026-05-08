#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    int odd = 0, even = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        if(i & 1) odd += s[i];
        else even += s[i];
    }

    if(odd % ((n + 1) / 2) == 0)
    if(even % (n / 2) == 0)
    if(odd / ((n + 1) / 2) == even / (n / 2))
    {
        cout << "YES" << endl;
        return;
    }

    cout << "NO" << endl;
    return;
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