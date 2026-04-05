#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <stack>
using namespace std;
#define int long long

void solve()
{
    // https: // codeforces.com/contest/2157
    int n, x, y;
    cin >> n >> x >> y;
    x = abs(x), y = abs(y);
    vector<char> s(n + 1);
    int a = 0, b = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        if (s[i] == '4')
        {
            a++;
        }
        else
        {
            b++;
        }
    }
    if (x <= b && y <= b)
    {
        cout << "YES" << endl;
        return;
    }

    x -= b, y -= b;
    x = max(x, 0ll), y = max(y, 0ll);

    if (x + y <= a)
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