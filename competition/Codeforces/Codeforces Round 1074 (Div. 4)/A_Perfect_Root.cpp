#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cout << i << " ";
    }
    cout << endl;

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