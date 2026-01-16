#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    int found = 0;
    for (int i = 1; i <= 50000; i++)
    {
        if((int)(i * 1.08) == n)
        {
            cout << i << endl;
            found = 1;
            break;
        }
    }

    if(!found)
    {
        cout << ":(" << endl;
    }

    return;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}