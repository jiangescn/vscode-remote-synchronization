#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    s = ' ' + s;

    int need = 0;
    int o = 0;
    for (int i = 1; i <= n; i++)
    {
        if(s[i] == '1')
        {
            o = 1;
        }

        if(o && s[i] == '0')
        {
            o = 0;
            need++;
        }
    }

    if(need & 1)
    {
        vector<int> ans;
        cout << "Alice" << endl;
        int fir = 1;
        int diff = 0;
        int i;
        for (i = 1; i <= n; i++)
        {
            if(s[i] == '0' && fir == 1)
            {
                continue;
            }
            fir = 0;
            
            if(s[i] != s[i-1])
            {
                diff++;
            }
            if(diff == 3)
            {
                break;
            }
            ans.push_back(i);
        }

        cout << ans.size() << endl;
        for (int i = 0; i < ans.size(); i++)
        {
            cout << ans[i] << " ";
        }cout << endl;
    }
    else
    {
        cout << "Bob" << endl;
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