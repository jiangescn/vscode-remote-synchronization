#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    string tar;
    cin >> tar;
    vector<string> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }
    int len = tar.size();

    vector<int> ans;
    for (int i = 1; i <= n; i++)
    {
        int sl = s[i].length();
        if(s[i] == tar)
        {
            ans.push_back(i);
            continue;
        }
        else if(sl + 1 == len || sl - 1 == len)
        {
            const string &shorter = (sl < len) ? s[i] : tar;
            const string &longer = (sl < len) ? tar : s[i];
            int l = 0, r = 0;
            int diff = 0;
            while (l < shorter.size() && r < longer.size())
            {
                if (shorter[l] == longer[r])
                {
                    l++;
                    r++;
                }
                else
                {
                    r++;
                    diff++;
                    if (diff > 1)
                        break;
                }
            }
            if (l == shorter.size() && diff <= 1)
            {
                ans.push_back(i);
            }
        }
        else if(sl == len)
        {
            int l = 0, r = 0;
            int diff = 0;
            while (l < len && r < sl)
            {
                if (s[i][l] != tar[r])
                {
                    diff++;
                    if (diff > 1)
                    {
                        break;
                    }
                }
                l++;
                r++;
            }
            if (diff <= 1)
            {
                ans.push_back(i);
            }
        }
    }
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " \n"[i==ans.size()-1];
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