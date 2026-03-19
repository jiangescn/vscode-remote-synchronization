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
    vector<pair<string, double>> s(1);
    for (int i = 1; i <= n; i++)
    {
        string a;
        double b;
        cin >> a >> b;
        s.push_back({a, b});
    }
    sort(s.begin() + 1, s.end(), [](auto x, auto y){
        if(x.second == y.second) return x.first < y.first;
        return x.second < y.second;
    });

    int count = 0;
    for (int i = 1; i <= n; i++)
    {
        if(s[i].second <= 3.0)
        {
            count++;
        }
    }

    cout << count << endl;
    for (int i = 1; i <= count; i++)
    {
        cout << s[i].first << endl;
    }   
    return;
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