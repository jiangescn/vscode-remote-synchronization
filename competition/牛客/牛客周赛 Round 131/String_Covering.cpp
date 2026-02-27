#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    if(n == 1 && s[0] == '0')
    {
        cout << "YES" << endl;
        return;
    }
    if(n == 1 && s[0] == '1')
    {
        cout << "NO" << endl;
        return;
    }

    if(s[0] == '1' && s[1] == '0' || s[n-1] == '1' && s[n-2] == '0')
    {
        cout << "NO" << endl;
        return;
    }

    for (int i = 1; i < n; i++)
    {
        if(s[i - 1] == '0' && s[i] ==  '1' && s[i + 1] == '0')
        {
            cout << "NO" << endl;
            return;
        }
    }

    cout << "YES" << endl; 
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