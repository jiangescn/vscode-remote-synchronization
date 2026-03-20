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
    int n, h, k;
    cin >> n >> h >> k;
    vector<int> s(n + 1);
    int once = 0;
    int time = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        once += s[i];
    }

    int round = h / once;
    time = round * (n + k);
    h -= round * once;
    if(h == 0)
    {
        time -= k;
        cout << time << endl;
        return;
    }


    vector<int> pre(n + 1);
    vector<int> premin(n + 1, INT_MAX);
    vector<int> sufmax(n + 2);
    for (int i = 1; i <= n; i++)
    {
        pre[i] = pre[i-1] + s[i];
        premin[i] = min(premin[i-1], s[i]);
    }
    for (int i = n; i >= 1; i--)
    {
        sufmax[i] = max(sufmax[i + 1], s[i]);
    }

    for (int i = 1; i <= n; i++)
    {
        int cur = pre[i];
        if(i < n)
        {
            cur = max(cur, pre[i] - premin[i] + sufmax[i + 1]);
        }

        if(cur >= h)
        {
            time += i;
            cout << time << endl;
            return;
        }
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