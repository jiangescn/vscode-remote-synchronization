#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    int have1 = 0;
    int have0 = 0;
    for (int i = 0; i < n; i++)
    {
        if(s[i] == '0')
        {
            have0 = 1;
        }
        else
        {
            have1 = 1;
        }
    }
    
    if(have1 == 0)
    {
        cout << 0 << endl;
    }
    else if(have0 == 0)
    {
        cout << n << endl;
    }
    else
    {
        cout << n - 1 << endl;
    }
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