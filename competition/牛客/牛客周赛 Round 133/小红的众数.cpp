#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, x;
    cin >> n >> x;
    map<int, int> s;
    int Max = 0;

    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        s[a]++;

        Max = max(Max, s[a]);
    }

    cout << max(0ll, Max - s[x]) << endl;
    

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