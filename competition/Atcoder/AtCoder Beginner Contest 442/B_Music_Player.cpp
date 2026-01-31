#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    int cur = 0;
    int stop = 1;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        if(x == 1)
        {
            cur++;
        }
        else if(x == 2 && cur > 0)
        {
            cur--;
        }
        else if(x == 3)
        {
            stop ^= 1;
        }


        if(cur >= 3 && stop== 0)
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
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