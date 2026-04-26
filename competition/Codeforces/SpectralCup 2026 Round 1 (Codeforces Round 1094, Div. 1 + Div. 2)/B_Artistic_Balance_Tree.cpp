#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> s(n + 1);
    vector<int> x(m + 1);
    int odd = 0, even = 0;
    vector<int> od;
    vector<int> ev;
    int sum = 0;

    bool fushuodd = 1;
    bool fushueven = 1;

    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        sum += s[i];
        if(i & 1) od.push_back(s[i]);
        else ev.push_back(s[i]);
    }

    for (int i = 1; i <= m; i++)
    {
        cin >> x[i];
        if(x[i] & 1) odd++;
        else even++;
    }

    sort(od.begin(), od.end(), greater<int>());
    sort(ev.begin(), ev.end(), greater<int>());

    for (int i = 0; i < od.size(); i++)
    {
        if(od[i] > 0) fushuodd = 0;
    }
    for (int i = 0; i < ev.size(); i++)
    {
        if (ev[i] > 0) fushueven = 0;
    }

    for (int i = 0; i < odd; i++)
    {
        if(i >= od.size() || od[i] <= 0) break;
        sum -= od[i];
    }
    for (int i = 0; i < even; i++)
    {
        if (i >= ev.size() || ev[i] <= 0) break;
        sum -= ev[i];
    }

    if(fushuodd && odd) sum -= od[0];
    if(fushueven && even) sum -= ev[0];

    cout << sum << endl;
    // cout << endl;
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