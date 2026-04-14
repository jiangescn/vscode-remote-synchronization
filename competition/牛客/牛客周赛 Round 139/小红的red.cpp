#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    string s;
    cin >> s;
    
    for (int i = 0; i < s.size(); i++)
    {
        if(s[i] == 'r') continue;
        if(s[i] == 'e') continue;
        if(s[i] == 'd') continue;
        cout << "No" << endl;
        return;
    }

    cout << "Yes" << endl;
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