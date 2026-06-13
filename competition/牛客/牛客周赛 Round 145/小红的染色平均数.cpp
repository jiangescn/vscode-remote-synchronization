#include <bits/stdc++.h>
using namespace std;
#define int long long
#define itn int

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }
    string clo;
    cin >> clo;
    clo = " " + clo;

    int sum_red = 0, sum_blue = 0;
    int count_red = 0, count_blue = 0;
    for (int i = 1; i <= n; i++)
    {
        if (clo[i] == '0')
        {
            sum_red += s[i];
            count_red++;
        }
        else
        {
            sum_blue += s[i];
            count_blue++;
        }
    }

    int t = count_red * sum_blue - count_blue * sum_red;

    if (t % n != 0)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << abs(t / n) << endl;
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