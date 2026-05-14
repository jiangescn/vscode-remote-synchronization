#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    set<int> st;
    int Max = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        st.insert(s[i]);
        Max = max(Max, s[i]);
    }

    int val = 0;
    for (int it : st)
    {
        if (it == val) val++;
        else break;
    }

    cout << Max * n + (val) * (val + 1) / 2 + (n - val - 1) * val + (Max == val - 1) << endl;
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