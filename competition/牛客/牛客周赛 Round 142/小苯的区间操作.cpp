#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    if(n == 1)
    {
        cout << (s[1] == 0 ? "Yes" : "No") << endl;
        return;
    }

    int ans = (s[1] > s[2]) + (s[n] > s[n - 1]);
    for (int i = 2; i < n; i++)
    {
        ans += (s[i] > s[i - 1] && s[i] > s[i + 1]);
    }

    if(ans)
    {
        cout << "No" << endl;
    }
    else
    {
        cout << "Yes" << endl;
    }
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