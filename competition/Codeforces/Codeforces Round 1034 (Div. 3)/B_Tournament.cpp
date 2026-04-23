#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    int j, k;
    cin >> j >> k;
    vector<int> s(n + 1);
    int Max = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        Max = max(Max, s[i]);
    }

    if(k == 1 && s[j] != Max)
    {
        cout << "NO" << endl;
    }
    else
    {
        cout << "YES" << endl;
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