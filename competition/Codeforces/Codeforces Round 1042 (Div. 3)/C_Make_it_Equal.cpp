#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    vector<int> b(n + 1);

    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    map<int, int> m1;
    map<int, int> m2;

    for (int i = 1; i <= n; i++)
    {
        int x = a[i] % k;
        m1[x]++;
        m1[k - x]++;
    }
    for (int i = 1; i <= n; i++)
    {
        int x = b[i] % k;
        m2[x]++;
        m2[k - x]++;
    }

    int ans = 1;
    for (auto it : m1)
    {
        if(it.second != m2[it.first]) ans = 0;
    }
    
    cout << (ans ? "YES" : "NO") << endl;

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