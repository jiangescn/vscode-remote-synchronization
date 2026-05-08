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


    for (int i = 2; i < n; i++)
    {
        if(s[i] > s[i - 1] && s[i] > s[i + 1])
        {
            int t = s[i] - max(s[i - 1], s[i + 1]);
            s[i] -= t;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        cout << s[i] << " \n"[i == n];
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