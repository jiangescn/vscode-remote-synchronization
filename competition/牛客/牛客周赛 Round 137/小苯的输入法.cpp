#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    deque<char> ans;

    int cur = 1;

    for (int i = 0; i < n; i++)
    {
        if(s[i] == '!')
        {
            cur ^= 1;
        }
        else if(s[i] == '-')
        {
            if(ans.empty()) continue;
            if(cur)
            {
                ans.pop_back();
            }
            else
            {
                ans.pop_front();
            }
        }
        else
        {
            if(cur) ans.push_back(s[i]);
            else ans.push_front(s[i]);
        }
    }

    if(ans.empty())
    {
        cout << "Empty" << endl;
        return;
    }

    for (char it : ans)
    {
        cout << it;
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