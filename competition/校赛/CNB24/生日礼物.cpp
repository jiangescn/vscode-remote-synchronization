#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int a, b, c;
        cin >> a >> b >> c;

        int x = a & 1, y = b & 1, z = c & 1;
        int cost1 = (x == 0) + (y == 1) + (z == 1);
        int cost2 = (x == 1) + (y == 0) + (z == 0);

        cout << min(cost1, cost2) << endl;       


    }
}