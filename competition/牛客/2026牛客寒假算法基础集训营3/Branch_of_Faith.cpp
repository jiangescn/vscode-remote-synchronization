#include <bits/stdc++.h>
using namespace std;
#define int long long

int qpow(int a, int b)
{
    int r = 1;
    while (b)
    {
        if (b & 1)
            r = r * a;
        a = a * a;
        b >>= 1;
    }
    return r;
}

void solve()
{
    int n, q;
    cin >> n >> q;

    while(q--)
    {
        int x;
        cin >> x;
        int cheng = 1;
        while((1ll << cheng) < x + 1)
        {   
            cheng++;
        }
        cheng --;
        // cout << cheng << '\n';
        // cout << qpow(2, cheng) << '\n';

        int thiscount = (1LL << cheng);
        int endnum = (1LL << (cheng + 1)) - 1;

        // cout << endnum << '\n';

        if(endnum > n)
        {
            cout << thiscount - (endnum - n) << '\n';
        }
        else
        {
            cout << thiscount << '\n';
        }

    }

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