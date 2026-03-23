#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int a, b, k;
    cin >> a >> b >> k;

    int Max = 0;
    
    if(b > a)
    {
        Max = 1;
        b -= k;
    }
    else
    {
        Max = 0;
        a -= k;
    }
    for (int i = 1; i <= k; i++)
    {
       cout << Max;
    }
    
    // cout << "a:" << a << endl;
    // cout << "b:" << b << endl;

    int round = min(a, b);
    if(round == 0)
    {
        if(a == 0)
        {
            for (int i = 1; i <= b; i++)
            {
                cout << 1;
            }
        }
        else
        {
            for (int i = 1; i <= a; i++)
            {
                cout << 0;
            }
        }
        return;
    }


    int oncea = a / round;
    int onceb = b / round;
    a %= round;
    b %= round;
    if(Max == 1)
    {
        for (int i = 1; i <= round; i++)
        {
            for (int j = 1; j <= oncea; j++)
            {
                cout << 0;
            }
            for (int j = 1; j <= onceb; j++)
            {
                cout << 1;
            }
        }
    }
    else
    {
        for (int i = 1; i <= round; i++)
        {
            for (int j = 1; j <= onceb; j++)
            {
                cout << 1;
            }
            for (int j = 1; j <= oncea; j++)
            {
                cout << 0;
            }
        }
    }

    if(Max = 1)
    {
        for (int j = 1; j <= a; j++)
            {
                cout << 0;
            }
            for (int j = 1; j <= b; j++)
            {
                cout << 1;
            }
    }
    else
    {
        for (int j = 1; j <= b; j++)
            {
                cout << 1;
            }
            for (int j = 1; j <= a; j++)
            {
                cout << 0;
            }
    }
    
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int _ = 1;
//    cin >> _;
    while(_--)
    {
        solve();
    }
    return 0;
}
