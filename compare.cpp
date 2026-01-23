#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    int n, k;
    if (!(cin >> n >> k))
        return 0;
    vector<int> m(n);
    ll M = 0, P = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> m[i];
        M += m[i];
        P += (ll)m[i] * (i + 1);
    }
    int N = 1 << n;
    for (int mask = 0; mask < N; ++mask)
    {
        if (__builtin_popcount(mask) != k)
            continue;
        ll MS = 0, PS = 0;
        for (int i = 0; i < n; i++)
            if (mask & (1 << i))
            {
                MS += m[i];
                PS += (ll)m[i] * (i + 1);
            }
        if (PS * M == P * MS)
        {
            cout << "Yes\n";
            return 0;
        }
    }
    cout << "No\n";
    return 0;
}
