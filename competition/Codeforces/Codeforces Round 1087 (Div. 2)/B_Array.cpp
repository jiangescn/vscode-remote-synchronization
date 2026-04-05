#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    for (int i = 1; i < n; i++)
    {
        int count1 = 0;
        int count2 = 0;
        for (int j = i + 1; j <= n; j++)
        {
            if(s[j] > s[i]) count1++;
            if(s[j] < s[i]) count2++;
        }
        cout << max(count1, count2) << " ";
    }

    cout << 0 << endl;
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