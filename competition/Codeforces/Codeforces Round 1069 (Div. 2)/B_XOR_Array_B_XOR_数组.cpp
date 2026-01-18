#include <bits/stdc++.h>
using namespace std;
#define int long long

void solv()
{
    int n, l, r;
    cin >> n >> l >> r;

    vector<int> prefix(n + 1);
    int val = 1;

    prefix[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        if (i == l - 1 || i == r)
        {
            if (l == 1)
            {
                prefix[i] = 0;
            }
            else
            {
                prefix[i] = 1;
            }
        }
        else
        {
            prefix[i] = ++val;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        cout << (prefix[i] ^ prefix[i - 1]);
        if (i < n)
        {
            cout << " ";
        }
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
        solv();
    }
    return 0;
}