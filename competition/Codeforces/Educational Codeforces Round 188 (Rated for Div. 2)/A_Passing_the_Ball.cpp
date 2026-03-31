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
    vector<int> ans(n + 2);
    int val = 1;
    while(!ans[val])
    {
        ans[val] = 1;
        if(s[val] == 'L') val--;
        if(s[val] == 'R') val++;
    }

    int count = 0;
    for (int i = 1; i <= n; i++)
    {
        if (ans[i])
            count++;
    }
    cout << count << endl;
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