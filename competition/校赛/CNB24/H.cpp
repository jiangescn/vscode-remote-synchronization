#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        if (n > 36)
        {
            cout << -1 << endl;
            continue;
        }

        for (int i = 0; i < n / 2; i++)
        {
            cout << "8";
        }
        for (int i = 0; i < n % 2; i++)
        {
            cout << "4";
        }
        cout << endl;
    }
}