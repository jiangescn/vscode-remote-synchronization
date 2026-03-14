#include <bits/stdc++.h>
using namespace std;
#define int long long
int x, y, n;
int max_x, max_y;
vector<int> breakx;
vector<int> breaky;

void qm(vector<vector<int>>& s)
{
    max_x = 0;
    max_y = 0;
    int Max = LLONG_MIN;
    for (int i = 1; i <= x; i++)
    {
        if(breakx[i])
        {
            continue;
        }
        for (int j = 1; j <= y; j++)
        {
            if(breaky[j])
            {
                continue;
            }
            if(s[i][j] >= Max)
            {
                Max = s[i][j];
                max_x = i;
                max_y = j;
            }
        }
    }
}

void solve()
{
    cin >> x >> y >> n;
    vector<vector<int>> s(x + 1, vector<int> (y + 1));
    for (int i = 1; i <= x; i++)
    {
        for (int j = 1; j <= y; j++)
        {
            cin >> s[i][j];
        }
    }

    breakx.resize(x + 1);
    breaky.resize(y + 1);

    while(n--)
    {
        qm(s);
        breakx[max_x] = 1;
        breaky[max_y] = 1;
    }


    for (int i = 1; i <= x; i++)
    {
        int firi = 1;
        if (breakx[i])
        {
            continue;
        }
        for (int j = 1; j <= y; j++)
        {
            if (breaky[j])
            {
                continue;
            }
            if(!firi)
            {
                cout << " ";
            }
            cout << s[i][j];
            firi = 0;
        }
        cout << endl;
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}