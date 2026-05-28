#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    string s;
    cin >> s;

    int count = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if(s[i] == 'T') count++;
    }

    for (int i = 1; i <= count; i++)
    {
        cout << 'T';
    }

    for (int i = 0; i < s.size(); i++)
    {
        if(s[i] == 'T')continue;
        cout << s[i];
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