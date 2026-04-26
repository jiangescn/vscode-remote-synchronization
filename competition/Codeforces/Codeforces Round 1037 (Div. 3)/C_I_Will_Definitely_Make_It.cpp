#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> s(1);
    int distance;
    for (int i = 1; i <= n; i++)
    {
        int a;
        cin >> a;
        if(i == k) distance = a;
        s.push_back(a);
    }

    sort(s.begin(), s.end());
    s.erase(unique(s.begin(), s.end()), s.end());
    k = lower_bound(s.begin(), s.end(), distance) - s.begin();

    for (int i = k; i < s.size(); i++)
    {
        int nextpeople = s[i] - s[i - 1];
        if(nextpeople > distance)
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