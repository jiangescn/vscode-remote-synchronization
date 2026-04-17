#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;
    map<string, int> s;
    for (int i = 1; i <= n; i++)
    {
        string x;
        int y;
        cin >> x >> y;
        s[x] += max(k, y);
    }

    int q;
    cin >> q;
    while(q--)
    {
        string x;
        cin >> x;
        cout << (s[x] ? to_string(s[x]) : "No Info") << endl;
    }
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