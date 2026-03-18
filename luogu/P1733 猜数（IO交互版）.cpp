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
    int l = 0, r = 1e9;
    while(l <= r)
    {
        int mid = l + (r - l) / 2;
        cout << mid << endl;
        int res;
        cin >> res;
        if(res == 0)
        {
            return;
        }
        else if(res == -1)
        {
            l = mid + 1;
        }
        else if(res == 1)
        {
            r = mid - 1;
        }
    }
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
        solve();
    }
    return 0;
}