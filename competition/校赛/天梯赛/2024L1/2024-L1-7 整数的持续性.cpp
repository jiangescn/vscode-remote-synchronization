#include <bits/stdc++.h>
using namespace std;
#define int long long

int mtp(int x)
{
    int r = 1;
    while(x)
    {
        r *= x % 10;
        x /= 10;
    }
    return r;
}

int count(int x)
{
    int cnt = 0;
    while(x / 10)
    {
        x = mtp(x);
        cnt++;
    }
    return cnt;
}

void solve()
{
    int l, r;
    cin >> l >> r;

    int ans = 0;
    unordered_map<int, set<int>> mp;
    for (int i = l; i <= r; i++)
    {
        int cnt = count(i);
        ans = max(ans, cnt);
        mp[cnt].insert(i);
    }

    cout << ans << endl;
    for (auto it: mp[ans])
    {
        if(it != *mp[ans].begin())
        {
            cout << " ";
        }
        cout << it;
    }
    cout << endl;

}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}