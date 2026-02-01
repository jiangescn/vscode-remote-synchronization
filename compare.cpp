#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    int sum = 0;

    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    // 从左到右约束：s[i] <= s[i-1] + 1
    for (int i = 2; i <= n; i++)
    {
        if (s[i] > s[i - 1] + 1)
        {
            sum += s[i] - (s[i - 1] + 1);
            s[i] = s[i - 1] + 1;
        }
    }

    // 从右到左约束：s[i] <= s[i+1] + 1
    for (int i = n - 1; i >= 1; i--)
    {
        if (s[i] > s[i + 1] + 1)
        {
            sum += s[i] - (s[i + 1] + 1);
            s[i] = s[i + 1] + 1;
        }
    }

    cout << sum << '\n';
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
