#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{

    int n;
    cin >> n;
    vector<int> s(n + 1);
    vector<int> pre2(n + 1, 0);
    vector<int> nxt0(n + 2, n + 1);

    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        pre2[i] = pre2[i - 1] + (s[i] == 2);
    }

    int last = n + 1;
    for (int i = n; i >= 1; i--)
    {
        nxt0[i] = last;
        if (s[i] == 0) last = i;
    }

    int ans = 0;
    int l = 1;

    while (l <= n)
    {
        ans++;

        int next0pos = nxt0[l];
        if (next0pos == n + 1)
        {
            break;
        }

        int r = next0pos - 1;
        if (s[l] > 0 || pre2[next0pos - 1] - pre2[l] > 0)
        {
            r++;
        }

        l = r + 1;
    }

    cout << ans << endl;
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