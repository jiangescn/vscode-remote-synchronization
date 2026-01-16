#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int n;
    cin >> n;

    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    int Max = -1;
    for (int i = 1; i <= n; i++)
    {
        if (s[i] >= Max)
        {
            Max = s[i];
            cout << -1 << endl;
        }
        else
        {
            for (int j = i - 1; j >= 0; j--)
            {
                if (s[j] > s[i])
                {
                    cout << j << endl;
                    break;
                }
            }
        }
    }

    return 0;
}