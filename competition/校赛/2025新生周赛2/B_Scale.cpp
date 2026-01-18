#include <bits/stdc++.h>
using namespace std;
#define int long long

void solv()
{
    int n, k;
    cin >> n >> k;
    char s[1010][1010] = {0};
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> s[i][j];
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if(i % k == 0)
        {
            for (int j = 1; j <= n; j++)
            {
                if (j % k == 0)
                    cout << s[i][j];
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
        solv();
    }
    return 0;
}

