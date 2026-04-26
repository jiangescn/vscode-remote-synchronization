#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    s = " " + s;

    map<pair<int, int>, int> mp;
    int countD = 0;
    int countK = 0;
    for (int i = 1; i <= n; i++)
    {
        if(s[i] == 'D')countD++;
        else if(s[i] == 'K') countK++;

        int t = __gcd(countK, countD);
        int d = countD / t;
        int k = countK / t;

        cout << ++mp[{d, k}] << " \n"[i == n];
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