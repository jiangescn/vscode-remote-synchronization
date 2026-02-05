#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    int diff = 0;
    int csum = 0;

    vector<int> d(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        vector<int> vi(i + 1, 0);
        for (int j = 1; j <= i; j++)
        {
            if (vi[s[i]] == 0)
            {
                vi[s[i]]++;
                diff++;
                // cout << "   NEW:" << s[i] << endl;
            }
            csum += diff;
        }
        d[i] = csum;
    }

    for (int i = 1; i <= n; i++)
    {
        cout << d[i] << " ";
    }
    cout << endl;

    // int sum = 0;
    // for (int i = 1; i <= n; i++)
    // {
    //     sum += d[i] * i;
    //     // cout << "   + " << d[i] * i << endl;
    // }

    // cout << sum << endl;
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