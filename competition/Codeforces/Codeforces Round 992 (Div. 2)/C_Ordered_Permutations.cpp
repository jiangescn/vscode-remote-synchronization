#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5;
void solve()
{
    int n, k;
    cin >> n >> k;
    int l = 1, r = n;
    if (n - 1 <= 62 && k > (1ll << (n - 1)))
    {
        cout << "-1" << endl;
        return;
    }

    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        if (n - i - 1 <= 62 && k > (1ll << (n - i - 1)))
        {
            s[r--] = i, k -= (1ll << (n - i - 1));
        }
        else
        {
            s[l++] = i;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        cout << s[i] << " ";
    }
    cout << endl;
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
