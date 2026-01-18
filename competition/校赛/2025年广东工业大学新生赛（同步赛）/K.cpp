#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int n, m;
    cin >> n >> m;
    int sum = 0;

    for (int i = 0; i < n; i++)
    {
        int p, q, w;
        cin >> p >> q >> w;

        int need = m * p / q;
        if(m * p % q) need++;
        sum += max(need - w, (long long)0);
    }
    cout << sum << endl;
}