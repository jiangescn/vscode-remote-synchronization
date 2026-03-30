#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }
    
    vector<int> pre(n + 1);
    // vector<int> ppre(n + 1);
    for (int i = 1; i <= n; i++)
    {
        pre[i] = pre[i - 1] ^ s[i];
    }
    // for (int i = 1; i <= n; i++)
    // {
    //     ppre[i] = ppre[i - 1] ^ pre[i];
    // }
    for (int i = 1; i <= n; i++)
    {
        cout << pre[i] << " ";
    }cout << endl;
    // for (int i = 1; i <= n; i++)
    // {
    //     cout << ppre[i] << " ";
    // }cout << endl;


    // cout << ppre[n] << endl;





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