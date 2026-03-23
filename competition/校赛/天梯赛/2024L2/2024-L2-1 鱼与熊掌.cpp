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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        for (int j = 1; j <= x; j++)
        {
            int a; cin >> a;
            s[i].push_back(a);
        }
    }

    int q;
    cin >> q;
    while(q--)
    {
        int a, b;
        cin >> a >> b;
        int count = 0;
        for (int i = 1; i <= n; i++)
        {
            if(find(s[i].begin(), s[i].end(), a) != s[i].end())
            {
                if (find(s[i].begin(), s[i].end(), b) != s[i].end())
                {
                    count++;
                }
            }
        }
        cout << count << endl;
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