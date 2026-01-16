#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
    }

    deque<int> dq;
    for (int i = 0; i < n; i++)
    {
        dq.push_back(s[i]);
        int len = dq.size();
        if (len > 3 && dq[len - 1] == dq[len - 2] && dq[len - 2] == dq[len - 3] && dq[len - 3] == dq[len - 4])
        {
            int tar = dq.back();
            while (len != 0 && (dq.back() == tar))
            {
                dq.pop_back();
                len = dq.size();
            }
        }
    }
    // for (int i = 0; i < dq.size(); i++)
    // {
    //     cout << dq[i] << " ";
    // }cout << endl;
    
    cout << dq.size() << endl;
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