#include <bits/stdc++.h>
using namespace std;
#define int long long

int hiuwen(int x)
{
    int t = 0;
    while(x != 0)
    {
        t *= 10;
        t += x % 10;
        x /= 10;
    }
    return t;
}

void solve()
{
    int n;
    cin >> n;

    map<int, int> s;
    for (int i = 1; i * i <= 1e9; i++)
    {
        s[i * i] = 1;
    }

    // cout << hiuwen(n) << endl;

    if(s[n] && hiuwen(n) == n)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
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