#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    int Max = 0;
    int idx;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        if(s[i] > Max)
        {
            Max = s[i];
            idx = i;
        }
    }

    swap(s[1], s[idx]);
    for (int i = 1; i <= n; i++)
    {
        cout << s[i] << " ";
    }

    cout << endl;
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