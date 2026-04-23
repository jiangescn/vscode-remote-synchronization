#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
vector<vector<pair<int, int>>> s;

void solve()
{
    int n, m;
    cin >> n >> m;
    s.resize(n + 1);
    for (int i = 1; i <= m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;

        s[a].push_back({b, c});
    }

    for (int i = 1; i <= n; i++)
    {
        sort(s[i].begin(), s[i].end(), [](pair<int, int> a, pair<int, int> b){
            if(a.second == b.second) return a.first < b.first;
            else return a.second > b.second;
        });
    }

    int q;
    cin >> q;
    while(q--)
    {
        int x;
        cin >> x;

        int fir = 0;

        vector<int> vi(n + 1);
        // ans.resize(0);

        // dfs(x);

        int cur = x;
        while(s[cur].size() != 0)
        {
            if(fir) cout << "->";
            fir = 1;
            cout << cur;

            // cout << endl;
            // cout << "option:";
            // for (int i = 0; i < s[cur].size(); i++)
            // {
            //     if(vi[s[cur][i].first]) continue;
            //     cout << s[cur][i].first << " ";
            // }cout << endl;

            vi[cur] = 1;
            for (int i = 0; i < s[cur].size(); i++)
            {
                if (vi[s[cur][i].first]) continue;
                cur =  s[cur][i].first;
                break;
            }

            if(vi[cur])break;
        }

        if (s[cur].size() == 0)
        {
            cout << cur;
        }

        cout << endl;
    }

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