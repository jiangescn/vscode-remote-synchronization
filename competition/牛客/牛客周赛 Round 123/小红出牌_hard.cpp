#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 2);
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int a;
        cin >> a;
        s[a]++;
        if(s[a - 1] >= s[a] && s[a + 1] >= s[a])
        {
            ans--;
        }
        else if(s[a - 1] < s[a] && s[a + 1] < s[a])
        {
            ans++;
        }
        cout << ans << " ";
    }
    cout << endl;

}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}