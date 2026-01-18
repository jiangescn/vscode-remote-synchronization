#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        int Min = 10;
        while (n != 0)
        {
            int a = n % 10;
            Min = min(Min, a);
            n /= 10;
        }
        cout << Min << endl;
    }

    return 0;
}