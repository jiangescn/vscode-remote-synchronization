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
    vector<pair<int, int>> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i].first >> s[i].second;
    }

    int ans = 0;
    sort(s.begin() + 1, s.end(), [](pair<int, int> a, pair<int, int> b){
        return a.first > b.first;
    });
    for (int i = 1; i <= n; i++)
    {
        if(s[i].second  < m)
        {
            ans += s[i].second * s[i].first;
            m -= s[i].second;
        }
        else
        {
            ans += s[i].first * m;
            break;
        }
    }

    cout << ans << endl;
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