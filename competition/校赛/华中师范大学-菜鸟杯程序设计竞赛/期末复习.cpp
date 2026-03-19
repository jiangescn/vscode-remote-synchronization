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
    int m, n;
    int k;
    cin >> m >> n >> k;
    if (n == 1 || m == 1)
    {
        cout << -1 << endl;
        return;
    }

    int mn = min(m, n);
    int need = (m * n * 3 + 4) / 5;

    auto check = [&](int x) -> int
    {
        int bg = m + n - 1;
        int ed = bg - (x - 1) * 2;
        int sum = (bg + ed) * x / 2;
        return sum >= need;
    };

    int l = 1, r = mn;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (check(mid))
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    cout << l * k << endl;
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