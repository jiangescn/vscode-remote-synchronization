#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    string s;
    cin >> s;
    vector<vector<char>> ans(110);
    int count = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(')
        {
            count++;
        }
        else if (s[i] == ')')
        {
            for (int k = 0; k < ans[count].size(); k++)
            {
                cout << ans[count][k];
            }
            cout << endl;
            ans[count].erase(ans[count].begin(), ans[count].end());
            count--;
        }
        else
        {
            ans[count].push_back(s[i]);
        }
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