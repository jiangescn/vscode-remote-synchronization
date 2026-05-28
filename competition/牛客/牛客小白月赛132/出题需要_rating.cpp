#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;

    int x = 1000;

    int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0;
    for (int i = 1; i <= n; i++)
    {
        int plus;
        cin >> plus;

        x += plus;
        
        if(x < 700) a++;
        else if(x < 1100) b++;
        else if(x < 1500) c++;
        else if(x < 2000) d++;
        else if(x < 2400) e++;
        else if(x < 2800) f++;
        else  g++;
    }

    cout << a << " " << b << " " << c << " " << d << " " << e << " " << f << " " << g << endl;
 
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