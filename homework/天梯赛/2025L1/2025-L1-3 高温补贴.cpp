#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int T, S, t;
    cin >> T >> S >> t;

    if(T >= 35 && t >= 33)
    {
        if(S == 1)
        {
            cout << "Bu Tie" << endl;
        }
        else
        {
            cout << "Shi Nei" << endl;
        }
        cout << T << endl;
    }
    else
    {
        if (S == 1)
        {
            cout << "Bu Re" << endl;
        }
        else
        {
            cout << "Shu Shi" << endl;
        }
        cout << t << endl;
    }
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