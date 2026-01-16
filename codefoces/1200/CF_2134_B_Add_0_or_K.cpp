#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> s(n);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
    }
    
    int mod = k + 1;
    for (int i = 0; i < n; i++)
    {
        int m = s[i] % mod;
        s[i] += m * k;
    }

    for (int i = 0; i < n; i++)
    {
        cout << s[i] << " ";
    }
    cout << endl;
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