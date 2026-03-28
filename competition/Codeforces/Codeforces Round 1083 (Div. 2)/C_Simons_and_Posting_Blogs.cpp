#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> s(n + 1, vector<int> (1, 0));
    for (int i = 1; i <= n; i++)
    {
        int l;
        cin >> l;
        for (int j = 1; j <= l; j++)
        {
            int a;
            cin >> a;
            s[i].push_back(a);
        }
        reverse(s[i].begin() + 1, s[i].end());
        vector<int> ss(1, 0);
        map<int, int> vi;
        for (int k = 1; k < s[i].size(); k++)
        {
            if(vi[s[i][k]]) continue;
            vi[s[i][k]] = 1;
            ss.push_back(s[i][k]);
        }
        s[i] = ss;
    }

    vector<int> used(1e6 + 10);    //已经出现在最终答案里的数字
    vector<int> del(n + 1);
    vector<int> ans;    //当前已经构造好的最终答案前缀

    for (int  i = 1; i <= n; i++)
    {
        int pick = -1;
        vector<int> best;

        for (int j = 1; j <= n; j++)
        {
            if(del[j]) continue;

            vector<int> cur;
            for (int k = 1; k < s[j].size(); k++)
            {
                if(!used[s[j][k]]) cur.push_back(s[j][k]);
            }

            if(pick == -1 || cur < best)
            {
                pick = j;
                best = cur;
            }
        }

        del[pick] = 1;
        for (auto it : best)
        {
            used[it] = 1;
            ans.push_back(it);
        }
    }

    for (auto it : ans)
    {
        cout << it << " ";
    }
    cout << endl;
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