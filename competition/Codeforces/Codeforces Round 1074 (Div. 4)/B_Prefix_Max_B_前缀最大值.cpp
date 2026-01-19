#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    int Max = 0;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        Max = max(Max, a);
    }
    cout << Max * n << endl;

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