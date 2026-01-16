#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m, c;
    cin >> n >> m >> c;
    vector<int> b(m + 1);
    for(int i = 1; i <= m; i++)
    {
        cin >> b[i];
    }
    int count = 0;
    for(int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = 1; j <= m; j++)
        {
            int a;
            cin >> a;
            sum += a * b[j];
        }
        if(sum > -c)
        {
            count++;
        }
    }
    cout << count << endl;
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