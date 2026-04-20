#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    string s;
    cin >> s;

    if(s.size() == 1)
    {
        cout << "NO" << endl;
        return;
    }

    int n = s.size();

    for (int i = n - 1; i >= 2; i--)
    {
        if(s[i] < '0')
        {
            s[i] += 10;
            s[i - 1] -= 1;
        }
        if(s[i] == '9')
        {
            cout << "NO" << endl;
            return;
        }
        else
        {
            s[i - 1] -= 1;
        }
    }


    if(s[1] < '0')
    {
        s[0] -= 1;
        s[1] += 10;
    }


    if(s[0] < '0')
    {
        cout << "NO" << endl;
        return;
    }

    string ss = s.substr(0, 2);
    int x = stoll(ss);

    if(x <= 18 && x >= 10)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
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