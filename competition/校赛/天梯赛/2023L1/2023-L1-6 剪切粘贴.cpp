#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    string s;
    cin >> s;
    int q;
    cin >> q;
    while (q--)
    {
        int n, m;
        cin >> n >> m;
        string a, b;
        cin >> a >> b;

        int len = m - n + 1;
        string t = s.substr(n - 1, len);
        s.erase(n - 1, len);

        int pos = s.find(a + b);
        if (pos == string::npos) pos = s.size();
        else pos += a.size();
        s.insert(pos, t);
    }
    cout << s << endl;
    return;
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