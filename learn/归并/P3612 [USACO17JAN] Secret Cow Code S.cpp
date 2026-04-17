#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <stack>
using namespace std;
#define int long long

void solve()
{
    string s;
    int n;
    cin >> s >> n;
    int N = s.size();

    while(n > N)
    {
        int t = N;
        while(t < n) t <<= 1;

        t /= 2;

        n -= (t + 1);
        if(n == 0) n = t;
    }

    cout << s[n - 1] << endl;
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