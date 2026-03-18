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
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }
    int sum = (s[1] + s[n]) / (n - 1);
    a[1] = (sum - (s[1] - s[2])) / 2;
    for (int i = 2; i < n; i++)
    {
        a[i] = ((s[i + 1] - s[i]) - (s[i] - s[i - 1])) / 2;
    }
    a[n] = (sum - (s[n] - s[n - 1])) / 2;

    for (int i = 1; i <= n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;

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