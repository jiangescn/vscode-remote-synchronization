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

int dsum(int x)
{
    int sum = 0;
    while(x != 0)
    {
        sum += x % 10;
        x /= 10;
    }
    return sum;
}

void solve()
{
    int n;
    cin >> n;
    int ans = 0;
    for (int i = n; i <= n + 100; i++)
    {
        if(i - dsum(i) == n)
        {
            ans++;
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