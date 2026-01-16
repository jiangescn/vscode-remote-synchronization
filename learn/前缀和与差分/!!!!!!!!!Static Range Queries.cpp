#include <iostream>
using namespace std;

#define int long long
#define N (int)1E7
int s[N];

signed main()
{
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++)
    {
        int l, r, v;
        cin >> l >> r >> v;

        s[l] += v;
        s[r + 1] -= v;
    }

    for (int i = 1; i <= n; i++)
    {
        s[i] += s[i - 1];
    }
    for (int i = 1; i <= n; i++)
    {
        s[i] += s[i - 1];
    }
    
    for (int i = 1; i <= q; i++)
    {
        int l, r;
        cin >> l >> r;
        cout << s[r] - s[l] << endl;
    }
    
    return 0;
}