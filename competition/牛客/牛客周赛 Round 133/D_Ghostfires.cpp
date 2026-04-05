#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int r = 0, g = 0, b = 0, rb = 0, gb = 0, rg = 0;
    cin >> r >> g >> b;
    while ((r > 0) + (g > 0) + (b > 0) > 1)
    {
        if (r <= g && r <= b) gb++, g--, b--;
        else if (g <= r && g <= b) rb++, r--, b--;
        else if (b <= r && b <= g) rg++, r--, g--;
    }

    if (g > 0)
    {
        cout << "G";
        while(rg--) cout << "RG";
        bool flg = false;
        while(gb--) cout << "BG", flg = true;
        if(flg) 
            while(rb--) cout << "BR";
        else
            while (rb--) cout << "RB";
    }
    else if (r > 0)
    {
        cout << "R";
        while(rg--) cout << "GR";
        bool flg = false;
        while(rb--) cout << "BR", flg = true;
        if(flg) 
            while(gb--) cout << "BG";
        else
            while (gb--) cout << "GB";
    }
    else
    {
        if (b > 0) cout << "B";
        while(gb--) cout << "GB";
        bool flg = false;
        while(rb--) cout << "RB", flg = true;
        if(flg) 
            while(rg--) cout << "RG";
        else
            while (rg--) cout << "GR";
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