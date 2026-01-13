#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> a(2 * n), b(2 * n), c(2 * n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        a[n + i] = a[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
        b[n + i] = b[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> c[i];
        c[n + i] = c[i];
    }

    int va = 1;
    int sum1 = 0;
    for (int i = 0; i < n; i++)
    {
        va = 1;
        for(int j = 0; j < n; j++)
        {
            if(a[j] >= b[i + j])
            {
                va = 0;
            }
        }
        if(va)sum1++;
    }

    va = 1;
    int sum2 = 0;
    for (int i = 0; i < n; i++)
    {
        va = 1;
        for (int j = 0; j < n; j++)
        {
            if (b[j] >= c[i + j])
            {
                va = 0;
            }
        }
        if (va)sum2++;
    }

    cout << sum1 * sum2 * n << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}