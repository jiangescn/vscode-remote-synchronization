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
    string ss;
    cin >> ss;
    ss = " " + ss;

    int Max = 1;
    int Min = 1;
    for (int i = 1; i <= n; i++)
    {
        if (s[i] > s[Max])
        {
            Max = i;
        }
        if (s[i] < s[Min])
        {
            Min = i;
        }
    }
    if (Min > Max) swap(Min, Max);

    if(ss[1] == '1' || ss[n] == '1')
    {
        cout << -1 << endl;
        return;
    }
    if(ss[Max] == '1' || ss[Min] == '1')
    {
        cout << -1 << endl;
        return;
    }

    cout << 5 << endl;

    cout << 1 << " " << Max << endl;
    cout << 1 << " " << Min << endl;
    cout << Max << " " << n << endl;
    cout << Min << " " << n << endl;
    cout << Min << " " << Max << endl;
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