#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int a, b;
    cin >> a >> b;
    vector<vector<int>> s(a + 1, vector<int>(b + 1));
    int count = 0;
    for (int i = 1; i <= a; i++)
    {
        for (int j = 1; j <= b; j++)
        {
            cin >> s[i][j];
            if (s[i][j])
            {
                count++;
            }
        }
    }


    int c = 0;
    int i, j;
    int need = (count + 1) / 2;

    for (i = a; i >= 1; i--)
    {
        for (j = 1; j <= b; j++)
        {
            if (s[i][j])
            {
                c++;
            }
            if (c >= need)
            {
                goto END;
            }
        }
    }

END:

    cout << c * (count - c) << endl;

    for (int x = 1; x < i; x++)
    {
        cout << 'D';
    }
    for (int y = 1; y <= j; y++)
    {
        cout << 'R';
    }
    cout << 'D';
    for (int y = j + 1; y <= b; y++)
    {
        cout << 'R';
    }
    for (int x = i + 1; x <= a; x++)
    {
        cout << 'D';
    }

    cout << endl;
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