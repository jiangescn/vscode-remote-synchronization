#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int a, b, c, m;
    cin >> a >> b >> c >> m;

    int abc = lcm(lcm(a, b), lcm(a, c));

    //a
    int ab = lcm(a, b);
    int ac = lcm(a, c);

    cout << m / a * 6 - (m / ab) * 3 - (m / ac) * 3 + (m / abc) * 2 << " "; 
    //b
    int ba = lcm(a, b);
    int bc = lcm(b, c);

    cout << m / b * 6 - (m / ba) * 3 - (m / bc) * 3 + (m / abc) * 2 << " "; 
    //c
    int ca = lcm(c, a);
    int cb = lcm(c, b);

    cout << m / c * 6 - (m / ca) * 3 - (m / cb) * 3 + (m / abc) * 2 << endl; 
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