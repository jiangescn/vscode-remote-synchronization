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
    vector<vector<int>> s(n + 1);
    for (int i = 1; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        s[a].push_back(b);
        s[b].push_back(a);
    }

    int x;
    cin >> x;
    if (n % 2 == 0 || s[x].size() <= 1)
    {
        cout << "xiaonian wins!" << endl;
    }
    else
    {
        cout << "coldtree wins!" << endl;
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}