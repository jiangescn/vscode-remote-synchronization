#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int m, n;
    cin >> m >> n;
    int ans = 0;
    deque<int> dq;

    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        for (int i = 0; i < dq.size(); i++)
        {
            if(dq[i] == a)
            {
                goto next;
            }
        }
        
        if(dq.size() >= m)
        {
            dq.pop_front();
        }
        dq.push_back(a);
        ans++;
        next:;
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