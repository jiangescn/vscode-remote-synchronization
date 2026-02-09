#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, q, b;
    cin >> n >> q >> b;
    vector<int> s(n + 1);
    vector<int> begn(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }
    int sum = b;
    for (int i = 1; i <= n; i++)
    {
        begn[i] = sum;
        sum += s[i];
    }

    // for (int i = 1; i <= n; i++)
    // {
    //     cout << begn[i] << endl;
    // }


    while(q--)
    {
        int xx, yy;
        cin >> xx >> yy;
        cout << begn[xx] + yy - 1 << endl;
    }




}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}