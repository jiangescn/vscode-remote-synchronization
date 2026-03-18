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
    int a, b;
    cin >> a >> b;
    if(abs(a - b) == 0 || abs(a - b) % 2 == 1)
    {
        cout << "Alice" << endl;
    }
    else
    {
        cout << "Bob" << endl;
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