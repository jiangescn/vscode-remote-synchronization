#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> s(n);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
    }
    vector<int> jc(m);
    for (int i = 0; i < m; i++)
    {
        cin >> jc[i];
    }

    int lm = 0, rm = 0;
    int pos = 0;
    for (int i = 0; i < k; i++)
    {
        char c;cin >> c;
        if(c == 'L')pos--;
        if(c == 'R')pos++;
        lm = min(lm, pos);
        rm = max(rm, pos);
    }

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