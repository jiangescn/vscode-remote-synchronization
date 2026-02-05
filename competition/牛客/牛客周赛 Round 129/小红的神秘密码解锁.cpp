#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    string s;
    cin >> s;
    int n = s.size();
    int a = 0, b = 0;
    for (int i = 1; i < n; i++)
    {
        if(s[i] == s[i - 1])
        {
            a++;
        }
        else
        {
            b++;
        }
    }
    cout << a * b + 1 << endl;
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