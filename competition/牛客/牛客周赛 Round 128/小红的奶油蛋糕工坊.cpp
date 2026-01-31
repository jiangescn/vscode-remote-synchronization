#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
    }

    int seam = n / 2;
    if (n & 1)
    {
        seam += 1;
    }

    // cout << "need:" << seam << endl;

    int tar = seam / 2;
    if (seam & 1)
    {
        tar++;
    }
    for (int i = 0; i < n; i++)
    {
        if (s[i] <= seam)
        {
            s[i] = tar;
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << s[i] << " ";
    }
    cout << endl;
    return;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}