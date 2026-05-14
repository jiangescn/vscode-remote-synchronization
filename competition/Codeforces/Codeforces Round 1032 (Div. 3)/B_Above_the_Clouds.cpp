#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    map<char, int> vi;
    for (int i = 0; i < n; i++)
    {
        vi[s[i]]++;
    }
    for (int i = 1; i < n - 1; i++)
    {
        if (vi[s[i]] > 1)
        {
            cout << "Yes" << endl;
            return;
        }
    }

    cout << "No" << endl;
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