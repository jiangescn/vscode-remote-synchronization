#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 2);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    int count = 0;
    for (int i = 1; i <= n; i++)
    {
        if (i % 2 == 0)
        {
            int sum = s[i - 1] + s[i + 1];
            if (sum > s[i])
            {
                if (sum - s[i] > s[i + 1])
                {
                    count += sum - s[i];
                    s[i + 1] = 0;
                    s[i] -= s[i + 1];
                    s[i - 1] -= sum - s[i] - s[i + 1];
                }
                else
                {
                    count += sum - s[i];
                    s[i + 1] -= sum - s[i];
                }
            }
        }
    }
    cout << count << endl;
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