#include <iostream>
using namespace std;
#define int long long

signed main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n, m, x, y;
        cin >> n >> m >> x >>y;

        if(n == 1 || m == 1)
        {
            if(n == 1 && m == 1)
            {
                cout << 0 << endl;
                continue;
            }
            cout << 1 << endl;
            continue;
        }

        cout << min(n ,m) + 1 << endl;
    }
}