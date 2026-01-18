#include <bits/stdc++.h>
using namespace std;
#define int long long

bool is(int x)
{
    // cout << "cur:" << x << endl;
    int a = x * x;
    int sum = 0;
    while (a != 0)
    {
        sum += a % 10;
        // cout << a % 10 << endl;
        a /= 10;
    }
    // cout << "sum:" << sum << " a:" << a << endl;
    return (sum == x);
}

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int a, b;
        cin >> a >> b;
        int count = 0;
        for (int i = a; i <= b; i++)
        {
            if (is(i))
                count++;
            if(i > 256)
            {
                break;
            }
        }
        cout << count << endl;
    }
}