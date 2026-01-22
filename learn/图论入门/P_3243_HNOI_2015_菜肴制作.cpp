#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<vector<int>> s(n+1);
    vector<int> ru(n+1);
    for (int i = 0; i < q; i++)
    {
        int a, b;
        cin >> a >> b;
        s[b].push_back(a);
        ru[a]++;
    }

    priority_queue<int> pq;
    vector<int> toposort;
    for (int i = 1; i <= n; i++)
    {
        if(!ru[i])
        {
            pq.push(i);
        }
    }

    while(!pq.empty())
    {
        int temp = pq.top();
        pq.pop();
        toposort.push_back(temp);

        for (int it: s[temp])
        {
            if(!(--ru[it]))
            {
                pq.push(it);
            }
        }
    }

    if (toposort.size() != n)
    {
        cout << "Impossible!" << endl;;
    }
    else
    {
        for (int i = n - 1; i >= 0; --i)
        {
            cout << toposort[i] << " \n"[i == 0];
        }
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