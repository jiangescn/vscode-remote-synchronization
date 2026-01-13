#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main()
{
    int t;
    cin >> t;
    while(t--)
    {
        long long a, b, n;
        cin >> a >> b >> n;

        long long maxcon = a / b;

        if(b * n <= a)
        {
            cout << 1 << endl;
        }
        else if(b == a)
        {
            cout << 1 << endl;
        }
        else
        {
            cout << 2 << endl;
        }
    }
}