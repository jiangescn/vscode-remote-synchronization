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
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    vector<int> s(1, 0);
    s.push_back(b[1]);
    for (int i = 2; i <= n; i++)
    {
        if (b[i] != b[i - 1])
        {
            s.push_back(b[i]);
        }
    }

    int idx = 1;
    for (int i = 1; i <= n && idx < (int)s.size(); i++)
    {
        if (a[i] == s[idx])
        {
            idx++;
        }
    }

    if (idx == (int)s.size())
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