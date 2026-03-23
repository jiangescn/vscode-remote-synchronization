#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int x, y, z;
    cin >> x >> y >> z;
    string a, b, s;
    cin >> a >> b >> s;
    
    string ans = "";
    for (int i = 0; i < z; i++)
    {
        // cout << "com: " << i << " ";
        if(i + x > z)
        {
            ans += s[i];
            // cout << "tobig" << endl;
            continue;
        }
        int ok = 1;
        for (int j = 0; j < x && j + i < z; j++)
        {
            if(a[j] != s[i + j])
            {
                ok = 0;
            }
        }

        // cout << ok << endl;

        if(!ok)
        {
            ans += s[i];
        }
        else
        {
            ans += b;
            i += x - 1;
        }
    }

    cout << ans << endl;

    
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int _ = 1;
//    cin >> _;
    while(_--)
    {
        solve();
    }
    return 0;
}
