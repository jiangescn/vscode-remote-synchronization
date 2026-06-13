#include <bits/stdc++.h>
using namespace std;
// #define int long long
// #define itn int

void solve()
{
    int n, k;
    cin >> n >> k;

    while(k--)
    {
        if(n > 2)
        {
            double t = sqrt(n);
            if(t - (int)t) t++;

            n = (int)t;
        }
        else
        {
            k++;
            n -= k;
            break;
        }
    }

    cout << n << '\n';

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