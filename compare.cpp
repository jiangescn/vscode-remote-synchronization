#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n + 1), stk(n + 1), L(n + 1), R(n + 1);
    int top = 0;

    for (int i = 1; i <= n; i++) cin >> a[i];

    top = 0;
    for (int i = 1; i <= n; i++) {
        while (top && a[stk[top]] < a[i]) top--;
        L[i] = top;
        stk[++top] = i;
    }

    top = 0;
    for (int i = n; i >= 1; i--) {
        while (top && a[stk[top]] < a[i]) top--;
        R[i] = top;
        stk[++top] = i;
    }

    int res = n;
    for (int i = 1; i <= n; i++) {
        res = min(res, n - (L[i] + R[i] + 1));
    }

    cout << res << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}