#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int a, b;
    cin >> a >> b;

    if (a >= b)
    {
        int time = b + 1;
        int one = a / time;
        int shengxia = a % time;
        string ans;
        for (int i = 0; i < time; ++i)
        {
            int len = one;
            if(i < shengxia) len++;
             while (len--) cout << '0';
            if (i < b)
            cout << '1';
        }
        cout << endl;
    }
    else
    {
        int time = a + 1;
        int one = b / time;
        int shengxia = b % time;
        string ans;
        for (int i = 0; i < time; ++i)
        {
            int len = one;
            if(i < shengxia) len++;
             while (len--) cout << '1';
            if (i < a)
            cout << '0';
        }
        cout << endl;
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