#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> s(n + 3);
    vector<int> l(n + 3);
    vector<int> r(n + 3);

    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    for (int i = 1; i <= n; i++)
    {
        l[i] = l[i - 1] + (s[i] <= k);
    }

    for (int i = n; i >= 1; i--)
    {
        r[i] = r[i + 1] + (s[i] <= k);
    }

    int left = -1, right = -1;

    for (int i = 1; i <= n; i++)
    {
        if (l[i] * 2 >= i)
        {
            if (left != -1 && l[i] > 1)
            {
                cout << "YES" << endl;
                return;
            }

            left = i;
        }
    }

    for (int i = n; i >= 1; i--)
    {
        if (r[i] * 2 >= n - i + 1)
        {
            if (right != -1 && r[i] > 1)
            {
                cout << "YES" << endl;
                return;
            }

            right = i;
        }
    }

    if (left != -1 && right != -1 && left < right)
    {
        cout << "YES" << endl;
        return;
    }

    cout << "NO" << endl;
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