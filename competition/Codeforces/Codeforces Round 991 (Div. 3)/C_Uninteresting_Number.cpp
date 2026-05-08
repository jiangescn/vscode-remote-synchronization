#include <bits/stdc++.h>
using namespace std;
#define int long long


void solve()
{
    string s;
    cin >> s;
    int n = s.size();

    int count2 = 0;
    int count3 = 0;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += s[i] - '0';
        if (s[i] == '2') count2++;
        if (s[i] == '3') count3++;
    }

    for (int i = 0; i <= count2; i++)
    {
        for (int j = 0; j <= count3; j++)
        {
            if ((sum + i * 2 + j * 6) % 9 == 0)
            {
                cout << "YES" << endl;
                return;
            }
        }
    }
    cout << "NO" << endl;
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