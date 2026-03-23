#include <bits/stdc++.h>
using namespace std;
// #define int long long

// const int N = 1e9 + 1;
// vector<int> dp;
vector<double> s(1, 0);

void solve()
{
    int m, n;
    cin >> m >> n;

    int found = 0;
    double Min = 1e9;
    for (int i = 1; i <= n; i++)
    {
        string st;
        double a, c;
        cin >> st >> a >> c;
        if(st == "FemboyLovestory")
        {
            Min = min(Min, a * c / 100);
            found = 1;
        }
        else
        {
            s.push_back(a * c / 100);
        }
    }

    m = m - Min;
    n = s.size() - 1;

    if(m == 0)
    {
        cout << 1 << endl;
        return;
    }
    else if(m < 0)
    {
        cout << 0 << endl;
        return;
    }

    // dp.resize(m + 1);
    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = m; j >= s[i]; j--)
    //     {
    //         dp[j] = max(dp[j], (dp[j - s[i]] + 1));
    //     }
    // }
    
    
    // if(found)cout << dp[m] + 1 << endl;
    // else cout << 0 << endl;

    int count = 0;
    sort(s.begin() + 1, s.end());
    // for (int i = 1; i <= n; i++)
    // {
    //     cout << s[i] << " ";
    // }cout << endl;


    for (int i = 1; i <= n; i++)
    {
        if(m - s[i] >= 0)
        {
            m -= s[i];
            count++;
        }
    }
    cout << count + 1 << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int _ = 1;
    // cin >> _;
    while(_--)
    {
        solve();
    }
    return 0;
}
