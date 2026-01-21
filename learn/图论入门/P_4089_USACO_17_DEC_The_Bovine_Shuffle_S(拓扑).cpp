#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> to(n+1);
    vector<int> ru(n+1);
    for (int i = 1; i <= n; i++)
    {
        cin >> to[i];
        ru[to[i]]++;
    }

    // cout << "ru: " << endl;
    // for (int i = 1; i <= n; i++)
    // {
    //     cout << ru[i] << " ";
    // }

    queue<int> q;
    vector<bool> remove(n+1, false);
    int ans = 0;

    for (int i = 1; i <= n; i++)
    {
        if(ru[i] == 0)
        {
            q.push(i);
        }
    }

    while(!q.empty())
    {
        int temp = q.front();
        q.pop();
        remove[temp] = true;

        int v = to[temp];
        ru[v]--;
        if (ru[v] == 0)
        {
            q.push(v);
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if(remove[i] == false)
        {
            ans++;
        }
    }

    cout << ans << endl;
    return;
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