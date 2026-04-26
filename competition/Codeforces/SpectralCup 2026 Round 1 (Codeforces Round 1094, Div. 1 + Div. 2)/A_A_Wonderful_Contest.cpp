#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    int ok = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        if(s[i] == 100) ok = 1;
    }

    cout << (ok ? "Yes" : "No") << endl;

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