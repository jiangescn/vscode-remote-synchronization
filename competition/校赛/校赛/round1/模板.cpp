#include <bits/stdc++.h>
using namespace std;
#define int long long

int f(int x)
{
    return x * x + 2 * x + 3;
}

void solve()
{
    int n;
    cin >> n;

    cout << f(f(f(n) + n) + f(f(n))) << endl;

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