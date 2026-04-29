#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, k;

void coutans(vector<vector<char>> &s)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << s[i][j];
        }
        cout << endl;
    }
    return;
}

void solve()
{
    cin >> n >> k;

    vector<vector<char>> s(n + 1, vector<char>(n + 1, 'U'));

    if (k == n * n - 1)
    {
        cout << "NO" << endl;
        return;
    }

    cout << "YES" << endl;

    if (k == n * n)
    {
        // cout << "  case0" << endl;
        coutans(s);
        return;
    }

    if (n == 2)
    {
        // cout << "  case1" << endl;
        if (k == 0)
        {
            cout << "DL" << endl;
            cout << "UL" << endl;
        }
        else if (k == 1)
        {
            cout << "DL" << endl;
            cout << "UR" << endl;
        }
        else if (k == 2)
        {
            cout << "DR" << endl;
            cout << "UR" << endl;
        }
        else if (k == 4)
        {
            cout << "UU" << endl;
            cout << "DD" << endl;
        }
        return;
    }

    s[n][1] = 'R';
    s[n][2] = 'L';

    int couldnot = n * n - k;
    if (couldnot <= n)
    {
        // cout << "  case2" << endl;
        for (int i = 1; i <= couldnot; i++)
        {
            if (i == 1 || i == 2) continue;
            s[n][i] = 'L';
        }
        coutans(s);
        return;
    }

    int count = 0;
    for (int i = 1; i <= n; i++)
    {
        if (i == 1 || i == 2) continue;
        s[n][i] = 'L';
    }
    // cout << "  case3" << endl;
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (count < k)
            {
                count++;
            }
            else
            {
                s[i][j] = 'D';
            }
        }
    }
    coutans(s);
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