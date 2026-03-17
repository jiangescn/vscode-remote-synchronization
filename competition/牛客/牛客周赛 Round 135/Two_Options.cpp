#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <string>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        sum += s[i];
    }

    int x = 0;
    if (sum >= 0)
    {
        x = sum / n;
        x += (sum % n != 0);
    }
    else
    {
        x = sum / n;
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (s[i] < x)
        {
            ans += x - s[i];
        }
    }
    cout << ans << endl;
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