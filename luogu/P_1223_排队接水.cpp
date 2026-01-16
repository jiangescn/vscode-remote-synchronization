#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<pair<int, int>> s(n);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i].second;
        s[i].first = i + 1;
    }
    
    sort(s.begin(), s.end(), [](pair<int, int> a, pair<int, int> b){
        return a.second < b.second;
    });

    vector<int> pre(n);
    pre[0] = s[0].second;
    for (int i = 1; i < n; i++)
    {
        pre[i] = pre[i-1] + s[i].second;
        //cout << pre[i] << " ";
    }

    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        cout << s[i].first << " ";
        sum += pre[i];
    }
    cout << endl;
    cout << fixed << setprecision(2) << (double)(sum - pre[n-1]) / n << endl;

    

}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}