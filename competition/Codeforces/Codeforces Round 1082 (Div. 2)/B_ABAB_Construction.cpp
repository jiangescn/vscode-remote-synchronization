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
    int n;
    cin >> n;
    string s;
    cin >> s;

    int ok = 1;

    if(n & 1)
    {
        if(s[0] == 'b')
        {
            cout << "NO" << endl;
            return;
        }
    }

    for (int i = n & 1; i < n - 1; i += 2)
    {
        if(s[i] != '?' && s[i + 1] != '?' && s[i] == s[i + 1])
        {
            cout << "NO" << endl;
            return;
        }
    }

    cout << "YES" << endl;
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