#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve ()
{
    int n, k;
    cin >> n >> k;
    vector <int> v(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }

    vector <int> premn(n + 10), premx(n + 10);
    premn[1] = v[1];
    premx[1] = v[1];
    for (int i = 2; i <= n; i++) {
        premn[i] = min(premn[i - 1], v[i]);
        premx[i] = max(premx[i - 1], v[i]);
    }
    vector <int> sufmn(n + 10), sufmx(n + 10);
    sufmn[n] = v[n];
    sufmx[n] = v[n];
    for (int i = n - 1; i >= 1; i--) {
        sufmn[i] = min(sufmn[i + 1], v[i]);
        sufmx[i] = max(sufmx[i + 1], v[i]);
    }

    int l = 1, r = k;
    int ans1 = -1, ans2 = 1e10;
    while (r <= n) {
        if (l == 1) {
            int c1 = sufmn[r + 1];
            int c2 = sufmx[r + 1];
            int t1 = c2 - c1;
            ans1 = max(ans1, t1);
            ans2 = min(ans2, t1);
            l++;
            r++;
            continue;
        }
        if (r == n) {
            int c1 = premn[l - 1];
            int c2 = premx[l - 1];
            int t1 = c2 - c1;
            ans1 = max(ans1, t1);
            ans2 = min(ans2, t1);
            l++;
            r++;
            break;
        }
        int cur1 = premn[l - 1];
        int cur2 = sufmn[r + 1];
        int cur3 = premx[l - 1];
        int cur4 = sufmx[r + 1];
        int c1 = min(cur1, cur2);
        int c2 = max(cur3, cur4);
        int t1 = c2 - c1;
        ans1 = max(ans1, t1);
        ans2 = min(ans2, t1);
        l++;
        r++;
    }

    cout << ans1 << ' ' << ans2 << '\n';
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