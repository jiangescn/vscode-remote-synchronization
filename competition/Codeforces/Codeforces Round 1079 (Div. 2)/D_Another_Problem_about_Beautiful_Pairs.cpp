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
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    int ans = 0;
    int B = sqrt(n) + 1;

    for (int j = 1; j <= n; j++)
    {
        int y = a[j];
        for (int x = 1; x <= B; x++)
        {
            int d = x * y;
            if (d >= j) break; // i = j - d >= 1     =>     d <= j-1
            int i = j - d;
            if (a[i] == x) ans++;
            
        }
    }

    for (int i = 1; i <= n; i++)
    {
        int x = a[i];
        if (x <= B)
            continue;

        for (int y = 1; y <= B; y++)
        {
            int j = i + x * y;
            if (j > n) break;
            if (a[j] == y) ans++;
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