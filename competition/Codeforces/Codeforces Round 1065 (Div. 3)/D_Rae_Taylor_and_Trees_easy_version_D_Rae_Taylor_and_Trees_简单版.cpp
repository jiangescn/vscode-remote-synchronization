#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> s(n + 1);
        vector<int> l(n + 1);
        vector<int> r(n + 1);

        for (int i = 1; i <= n; i++)
        {
            cin >> s[i];
        }

        if (n == 2)
        {
            cout << (s[1] < s[2] ? "Yes" : "No") << endl;
            continue;
        }

        int Min = s[1];
        for (int i = 1; i <= n; i++)
        {
            if (s[i] < Min)
            {
                Min = s[i];
            }
            l[i] = Min;
        }

        // for (int i = 1; i <= n; i++)
        // {
        //     cout << l[i] << " ";
        // }
        // cout << endl;

        int Max = s[n];
        for (int i = n; i >= 1; i--)
        {
            if (s[i] > Max)
            {
                Max = s[i];
            }
            r[i] = Max;
        }

        // for (int i = 1; i <= n; i++)
        // {
        //     cout << r[i] << " ";
        // }
        // cout << endl;
        // cout << endl;

        bool valid = true;
        for (int i = 2; i <= n - 1; i++)
        {
            if (l[i - 1] > r[i + 1])
                valid = false;
        }

        cout << (valid ? "Yes" : "No") << endl;
    }
    return 0;
}