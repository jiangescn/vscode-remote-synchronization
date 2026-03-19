#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <string>
using namespace std;
#define int long long

void solve()
{
    char a, b;
    cin >> a >> b;
    int x = a - 'A';
    int y = b - 'A';
    if(a == 'A' || a == 'B') x += 100;
    if(b == 'A' || b == 'B') y += 100;

    if(x >= y)
    {
        cout << a << endl;
    }
    else
    {
        cout << b << endl;
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