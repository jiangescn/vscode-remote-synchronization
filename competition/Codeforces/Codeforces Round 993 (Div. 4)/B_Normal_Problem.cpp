#include <bits/stdc++.h>
using namespace std;
#define int long long
#define itn int

void solve()
{
    string s;
    cin >> s;

    int n = s.size();
    s = " " + s;

    for (int i = n; i >= 1; i --)
    {
        if(s[i] == 'p')
        {
            cout << "q";
        }
        else if(s[i] == 'q')
        {
            cout << "p";
        }
        else
        {
            cout << s[i];
        }
    }
    cout << endl;

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