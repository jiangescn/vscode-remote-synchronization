#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    int count1 = 0, count0 = 0;
    for (auto it : s)
    {
        if (it - '0')
            count1++;
        else
            count0++;
    }

    int Min = abs(count1 - count0) / 2;
    int Max = n / 2 - (count0 & 1);

    // cout << Max << " " << Min << endl;

    if (k <= Max && k >= Min)
    {
        if ((k - Max) % 2 == 0)
        {
            cout << "YES" << endl;
            return;
        }
    }

    cout << "NO" << endl;
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