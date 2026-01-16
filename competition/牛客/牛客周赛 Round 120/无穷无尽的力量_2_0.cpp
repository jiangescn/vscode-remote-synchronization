#include <iostream>
using namespace std;
#define int long long

signed main()
{
    int n, m;
    cin >> n >> m;
    if(n > m)swap(n, m);

    if(n == 1)
    {
        cout << 1 << endl;
    }
    else if(n == 2 )
    {
        cout << (m - 1) / 2 + 1 << endl;
    }
    else
    {
        int ans = m * n;
        if(m == 3 && n == 3)
        {
            ans = 8;
        }
        cout << ans << endl;
    }
}