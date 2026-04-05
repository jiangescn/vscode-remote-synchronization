#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n * 2 + 1);
    for (int i = 1; i <= 2 * n; i++)
    {
        cin >> s[i];
    }

    vector<int> a(2 * n + 1), b(2 * n + 1);
    for (int i = 1; i <= 2 * n; i++)
    {
        if (i & 1)
        {
            a[i] = a[i - 1] + s[i], b[i] = b[i - 1];
        }
        else
        {
            b[i] = b[i - 1] + s[i], a[i] = a[i - 1];
        }
    }

    int temp = 0;
    for (int i = 1; i <= n; i++)
    {
        if (i & 1)
        {
            cout << temp + (b[2 * n - i + 1] - b[i - 1]) - (a[2 * n - i + 1] - a[i - 1]) << " ";
        }
        else
        {
            cout << temp + (a[2 * n - i + 1] - a[i - 1]) - (b[2 * n - i + 1] - b[i - 1]) << " ";
        }
        temp += s[2 * n - i + 1] - s[i];
    }
    cout << endl;
    return;
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