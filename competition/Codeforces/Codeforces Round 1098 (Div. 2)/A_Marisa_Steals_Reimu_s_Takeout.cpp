#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);

    int count0 = 0, count2 = 0;
    int count1 = 0;

    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];

        if (s[i] == 1)
            count1++;
        if (s[i] == 2)
            count2++;
        if (s[i] == 0)
            count0++;
    }

    int Min = min(count2, count1);

    int ans = count0 + Min + (count1 - Min) / 3 + (count2 - Min) / 3;

    cout << ans << endl;
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