#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve ()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector <int> c(26);
    for (int i = 0; i < n; i ++) {
        c[s[i] - 'a'] ++;
    }

    int cnt = 0;
    vector <int> res;
    for (int i = 0; i < 26; i ++) {
        if (c[i] & 1) {
            cnt++;
            res.push_back(i);
        }
    }

    int ans = 0;
    for (int i = 0; i < res.size(); i += 2) {
        ans += res[i + 1] - res[i];
    }
    
    cout << ans << '\n';
}

int32_t main ()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int _ = 1;
    // cin >> _;
    while (_--) {
        solve();
    }
    return 0;
}