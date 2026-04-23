#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s (n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    vector<int> ans;

    int Max = 0;
    int Min = INT_MAX;
    int sum = 0;

    for (int i = 1; i <= n; i++)
    {
        Max = max(Max, s[i]);
        Min = min(Min, s[i]);
        sum += s[i];
    }

    cout << Max << " " <<Min << " " << sum / n << endl;

    int fir = 0;
    for (int i = 1; i <= n; i++)
    {
        if(s[i] > sum / n * 2)
        {
            if(fir)
            cout << " ";
            cout << i;
            fir = 1;
        }
    }

    if(fir == 0)
    {
        cout << "Normal";
    }

}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}