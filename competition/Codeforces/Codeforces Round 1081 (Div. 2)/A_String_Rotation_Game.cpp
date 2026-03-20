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
    string s;
    cin >> s;
    map<char, int> count;
    int con = 1;
    int maxcon = 1;
    int ans = 1;
    for (int i = 0; i < n; i++)
    {
        count[s[i]]++;
    }
    for (int i = 1; i < n; i++)
    {
        if(s[i] == s[i - 1])
        {
            con++;
            maxcon = max(maxcon, con);
        }
        else
        {
            ans++;
            con = 1;
        }
    }
    // cout << "preans:" << ans << endl;

    if(count.size() > 1 && maxcon > 1 && s[0] != s[n - 1])
    {
        cout << ans + 1 << endl;
    }
    else
    {
        cout << ans << endl;
    }

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