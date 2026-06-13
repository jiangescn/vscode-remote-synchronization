#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    int Min = s[1];
    int Max = s[1];
    int sum = 0;

    for (int i = 1; i <= n; i++)
    {
        Max = max(Max, s[i]);
        Min = min(Min, s[i]);
        sum += s[i];
    }

    int count = 0;
    for (int i = 1; i <= n; i++)
    {
        if (s[i] == Max) count++;
    }

    if (Max - Min > k + 1)
    {
        cout << "Jerry" << endl;
        return;
    }

    if (Max - Min == k + 1 && count > 1)
    {
        cout << "Jerry" << endl;
        return;
    }

    if (sum & 1)
    {
        cout << "Tom" << endl;
    }
    else
    {
        cout << "Jerry" << endl;
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}