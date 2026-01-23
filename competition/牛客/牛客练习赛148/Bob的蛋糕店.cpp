#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<int> s(n);
    
    int m = 0, po = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
        m += s[i];
        po += s[i] * (i+1);
    }
    int N = 1 << n;
    for (int mask = 0; mask < N; mask++)
    {
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            if (mask & (1 << i))
            {
                count++;
            }
        }
        if (count != k)
            continue;

        int M = 0, Po = 0;
        for (int i = 0; i < n; i++)
        {
            if(mask & 1 << i)
            {
                M += s[i];
                Po += s[i] * (i + 1);
            }
        }

        if (Po * m == po * M)
        {
            cout << "Yes" << endl;;
            return;
        }
    }

    cout << "No" << endl;;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}