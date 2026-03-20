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
    vector<char> s(n + 1);
    int count1 = 0, count0 = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        if (s[i] == '1')
        {
            count1++;
        }
        else if (s[i] == '0')
        {
            count0++;
        }
    }

    // cout << "count1:" << count1 << "  count0:" << count0 << endl;

    if (count1 == 0)
    {
        cout << 0 << endl;
    }
    else if (count1 % 2 == 1 && count0 % 2 == 0)
    {
        cout << -1 << endl;
    }
    else
    {
        if (count1 % 2 == 0)
        {
            cout << count1 << endl;
            for (int i = 1; i <= n; i++)
            {
                if (s[i] == '1')
                {
                    cout << i << " ";
                }
            }
            cout << endl;
        }
        else if (count0 % 2 == 1)
        {
            cout << count0 << endl;
            for (int i = 1; i <= n; i++)
            {
                if (s[i] == '0')
                {
                    cout << i << " ";
                }
            }
            cout << endl;
        }
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