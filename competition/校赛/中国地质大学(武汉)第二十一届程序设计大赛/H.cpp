#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int mod = 1e9 + 7;
const int N = 2e4 + 3;

char *p1, *p2, buf[100000];
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++)

int read () {
    int x = 0, f = 1;
    char ch = gc();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = gc();
    }

    while ('0' <= ch && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = gc();
    }

    return x * f;
}

int cnt[N];
i64 cc[N];

void init () {
    for (int i = 1; i < N; i++) {
        cc[i] = i * i % mod;
    }
}

void solve ()
{
    int n, q;
    n = read();
    q = read();
    vector <int> v(n + 1);
    for (int i = 1; i <= n; i++) {
        v[i] = read();
    }

    map <array <int, 2> , int> mp;

    while (q--) {
        int l = read();
        int r = read();

        if (mp.find({l, r}) != mp.end()) {
            printf("%lld\n", mp[{l, r}]);
            continue;
        }
        int mx = r - l + 1;
        for (int i = l; i <= r; i++) {
            // cout << v[i] << ' ' << mx << '\n';
            if (v[i] >= mx) {
                cnt[r - l + 1]++;
            }else {
                cnt[v[i]]++;
            }
        }
        i64 ans = 0;
        int c = 0;

        for (int i = r - l + 1; i >= 1; i--) {
            c = (c + cnt[i]) % mod;
            ans = (ans + cc[c] * i % mod) % mod; 
        }

        printf("%lld\n", ans);
        // mp[{l, r}] = ans;
        for (int i = 1; i <= mx; i++) {
            cnt[i] = 0;
        }
    }

}

int32_t main ()
{
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    // int _ = 1;
    // cin >> _;
    init();
    // while (_--) {
        solve();
    // }
    return 0;
}