#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 1;
vector<int> s(1000, 0);

void solve()
{
    int n;
    cin >> n;

    int ans = 1;
    while (n > s[ans])
    {
        ans++;
    }
    cout << ans << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    s[0] = 0;
    s[1] = 1;
    for (int i = 2; s[i - 1] < maxn; i++)
    {
        s[i] = (s[i - 1] + 1) * 2;
    }

    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
