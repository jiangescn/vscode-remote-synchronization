#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m;
    cin >> n >> m;
    string a, b;
    cin >> a >> b;

    int j = 0;
    for (int i = 0; i < m; i++)
    {
        if (j >= n)
        {
            cout << "NO" << endl;
            return;
        }
        
        if (a[j] == b[i])
        {
            j++;
            continue;
        }

        int count = 0;
        if (b[i] == '0')
        {
            while (count < 2 && j < n)
            {
                if (a[j++] == '1') count++;
            }
            if (count < 2)
            {
                cout << "NO" << endl;
                return;
            }
        }

        else if (b[i] == '1')
        {
            while (count < 1 && j < n)
            {
                if (a[j++] == '1') count++;
            }
            if (count < 1)
            {
                cout << "NO" << endl;
                return;
            }
        }
    }

    int count = 0;
    for (int i = j; i < n; i++)
    {
        if (a[i] == '1')
        {
            count++;
        }
    }

    // cout << count << endl;

    if (count & 1)
    {
        cout << "NO" << endl;
    }
    else
    {
        cout << "YES" << endl;
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