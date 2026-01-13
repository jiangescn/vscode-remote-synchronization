#include <bits/stdc++.h>
using namespace std;
#define int long long

struct coin
{
    int m;
    int v;
    double x;
};

void solv()
{
    int n, t;
    cin >> n >> t;
    vector<coin> s(n);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i].m >> s[i].v;
        s[i].x = 1.0 * s[i].v / s[i].m;
    }

    sort(s.begin(), s.end(), [](coin a, coin b)
         { return a.x > b.x; });

    int i = 0;
    double ans = 0;
    while (t)
    {
        if (t >= s[i].m)
        {
            t -= s[i].m;
            ans += s[i].v;
        }
        else
        {
            ans += s[i].x * t;
            t = 0;
        }
        i++;
    }
    cout << fixed << setprecision(2) << ans << endl;
    return;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solv();
    }
    return 0;
}