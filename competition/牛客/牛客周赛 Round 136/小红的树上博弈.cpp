#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;

    vector<vector<int>> s(n + 1);
    for (int i = 1; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        s[a].push_back(b);
        s[b].push_back(a);
    }

    vector<int> good(n + 1, 0);
    vector<int> cnt(n + 1, 0);
    queue<int> q;

    for (int i = 2; i <= n; i++)
    {
        if(s[i].size() == 1)
        {
            good[i] = 1;
            q.push(i);
        }
    }

    while(!q.empty())
    {
        int x = q.front();
        q.pop();

        for (int it: s[x])
        {
            cnt[it]++;
            if(!good[it] && cnt[it] >= 2)
            {
                good[it] = 1;
                q.push(it);
            }
        }
    }

    int ok = 0;
    for (int it: s[1])
    {
        if(good[it])
        {
            ok = 1;
        }
    }

    cout << (ok ? "red" : "purple") << endl;
    return;
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