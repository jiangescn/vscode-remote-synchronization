#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 10000;
vector<bool> s(N * 10 , false);

void solve()
{
    int a;
    cin >> a;
    cout << (s[a] ? "Yes" : "No") << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    for (int i = 0; i <= 213; i++)
    {
        for (int j = 0; j <= 213; j++)
        {
            s[i * 47 + j * 352] = true;
        }
    }

    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}