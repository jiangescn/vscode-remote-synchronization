#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    int sum = 0, c2 = 0, c1 = 0, c0 = 0;

    for (int i = 1; i <= n; i++)
    {
        sum += s[i];

        if(s[i] == 2) c2++;
        if(s[i] == 0) c0++;
        if(s[i] == 1) c1++;
    }

    if(sum == k || k - sum >= 2)
    {
        cout << -1 << endl;
        return;
    }

    if(k < sum)
    {
        for (int i = 1; i <= n; i++)
        {
            cout << s[i] << " ";
        }
        cout << endl;
        return;
    }

    for (int i = 1; i <= c0; i++) cout << "0 ";
    for (int i = 1; i <= c2; i++) cout << "2 ";
    for (int i = 1; i <= c1; i++) cout << "1 ";

    cout << endl;


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