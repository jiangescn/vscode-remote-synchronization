#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;

    int Min = INT_MAX;
    map<int, int> count;
    for (int i = 1; i <= n; i++)
    {
        int a;
        cin >> a;
        count[a]++;
    }

    for (int i = 0; i <= 100; i++)
    {
        if(!count[i])
        {
            cout << i << endl;
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