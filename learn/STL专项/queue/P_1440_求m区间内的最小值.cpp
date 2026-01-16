#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> s(n);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
    }

    deque<int> dq;
    cout << 0 << endl;
    for (int i = 0; i < n; i++)
    {
        if(!dq.empty() && i - dq[0] >= k)
        {
            dq.pop_front();
        }
        while (!dq.empty() && s[i] < s[dq.back()])
        {
            dq.pop_back();
        }
        dq.push_back(i);

        if(i < n - 1) cout << s[dq[0]] << endl;
    }
    
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