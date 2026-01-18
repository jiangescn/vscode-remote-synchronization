#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int a[20] = {0};
    int b[20] = {0};
    for (int i = 0; i < 13; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < 13; i++)
    {
        cin >> b[i];
    }

    int more = 0, less = 0;
    for (int i = 0; i < 13; i++)
    {
        if(a[i] + b[i] > 4)
        {
            more += a[i] + b[i] - 4;
        }
        else
        {
            less += 4 - (a[i] + b[i]);
        }
    }
    
    cout << max(less, more) << endl;

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