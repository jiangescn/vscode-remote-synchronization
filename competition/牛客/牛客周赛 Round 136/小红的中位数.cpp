#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    int seam = 1;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        if (s[i] != s[1])
            seam = 0;
    }

    if (n == 1 || seam)
    {
        cout << -1 << endl;
        return;
    }

    sort(s.begin() + 1, s.end());
    int mid = (n + 1) / 2;
    int l = mid, r = mid;

    int idx = 0;
    if(n % 2 == 0) idx++;
    while (l >= 1 && r <= n && s[l] == s[mid] && s[r] == s[mid])
    {
        idx++;
        if (idx & 1)
        {
            l--;
        }
        else
        {
            r++;
        }
    }

    cout << max(1ll, idx - (n % 2 == 0)) << endl;
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