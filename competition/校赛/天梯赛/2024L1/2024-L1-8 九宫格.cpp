#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int s[10][10] = {0};
    for (int i = 1; i <= 9; i++)
    {
        for (int j = 1; j <= 9; j++)
        {
            cin >> s[i][j];
        }
    }

    int ok = 1;
    //hh
    for (int i = 1; i <= 9; i++)
    {
        vector<int> vi(10);
        for (int j = 1; j <= 9; j++)
        {
            vi[s[i][j]]++;
        }

        for (int k = 1; k <= 9; k++)
        {
            if(vi[k] != 1)
            {
                ok = 0;
            }
        }
    }
    //lp
    for (int j = 1; j <= 9; j++)
    {
        vector<int> vi(10);
        for (int i = 1; i <= 9; i++)
        {
            vi[s[i][j]]++;
        }

        for (int k = 1; k <= 9; k++)
        {
            if(vi[k] != 1)
            {
                ok = 0;
            }
        }
    }

    //gsww
    for (int i = 1; i <= 9; i++)
    {
        vector<int> vi(10);
        vi[s[1][1]]++, vi[s[1][2]]++,vi[s[1][3]]++;
        vi[s[2][1]]++, vi[s[2][2]]++,vi[s[2][3]]++;
        vi[s[3][1]]++, vi[s[3][2]]++,vi[s[3][3]]++;

        for (int k = 1; k <= 9; k++)
        {
            if (vi[k] != 1)
            {
                ok = 0;
            }
        }
    }
    for (int i = 1; i <= 9; i++)
    {
        vector<int> vi(10);
        vi[s[4][1]]++, vi[s[4][2]]++,vi[s[4][3]]++;
        vi[s[5][1]]++, vi[s[5][2]]++,vi[s[5][3]]++;
        vi[s[6][1]]++, vi[s[6][2]]++,vi[s[6][3]]++;

        for (int k = 1; k <= 9; k++)
        {
            if (vi[k] != 1)
            {
                ok = 0;
            }
        }
    }
    for (int i = 1; i <= 9; i++)
    {
        vector<int> vi(10);
        vi[s[7][1]]++, vi[s[7][2]]++,vi[s[7][3]]++;
        vi[s[8][1]]++, vi[s[8][2]]++,vi[s[8][3]]++;
        vi[s[9][1]]++, vi[s[9][2]]++,vi[s[9][3]]++;

        for (int k = 1; k <= 9; k++)
        {
            if (vi[k] != 1)
            {
                ok = 0;
            }
        }
    }
    for (int i = 1; i <= 9; i++)
    {
        vector<int> vi(10);
        vi[s[1][4]]++, vi[s[1][5]]++,vi[s[1][6]]++;
        vi[s[2][4]]++, vi[s[2][5]]++,vi[s[2][6]]++;
        vi[s[3][4]]++, vi[s[3][5]]++,vi[s[3][6]]++;

        for (int k = 1; k <= 9; k++)
        {
            if (vi[k] != 1)
            {
                ok = 0;
            }
        }
    }
    for (int i = 1; i <= 9; i++)
    {
        vector<int> vi(10);
        vi[s[4][4]]++, vi[s[4][5]]++,vi[s[4][6]]++;
        vi[s[5][4]]++, vi[s[5][5]]++,vi[s[5][6]]++;
        vi[s[6][4]]++, vi[s[6][5]]++,vi[s[6][6]]++;

        for (int k = 1; k <= 9; k++)
        {
            if (vi[k] != 1)
            {
                ok = 0;
            }
        }
    }
    for (int i = 1; i <= 9; i++)
    {
        vector<int> vi(10);
        vi[s[7][4]]++, vi[s[7][5]]++,vi[s[7][6]]++;
        vi[s[8][4]]++, vi[s[8][5]]++,vi[s[8][6]]++;
        vi[s[9][4]]++, vi[s[9][5]]++,vi[s[9][6]]++;

        for (int k = 1; k <= 9; k++)
        {
            if (vi[k] != 1)
            {
                ok = 0;
            }
        }
    }
    for (int i = 1; i <= 9; i++)
    {
        vector<int> vi(10);
        vi[s[1][7]]++, vi[s[1][8]]++,vi[s[1][9]]++;
        vi[s[2][7]]++, vi[s[2][8]]++,vi[s[2][9]]++;
        vi[s[3][7]]++, vi[s[3][8]]++,vi[s[3][9]]++;

        for (int k = 1; k <= 9; k++)
        {
            if (vi[k] != 1)
            {
                ok = 0;
            }
        }
    }
    for (int i = 1; i <= 9; i++)
    {
        vector<int> vi(10);
        vi[s[4][7]]++, vi[s[4][8]]++,vi[s[4][9]]++;
        vi[s[5][7]]++, vi[s[5][8]]++,vi[s[5][9]]++;
        vi[s[6][7]]++, vi[s[6][8]]++,vi[s[6][9]]++;

        for (int k = 1; k <= 9; k++)
        {
            if (vi[k] != 1)
            {
                ok = 0;
            }
        }
    }
    for (int i = 1; i <= 9; i++)
    {
        vector<int> vi(10);
        vi[s[7][7]]++, vi[s[7][8]]++,vi[s[7][9]]++;
        vi[s[8][7]]++, vi[s[8][8]]++,vi[s[8][9]]++;
        vi[s[9][7]]++, vi[s[9][8]]++,vi[s[9][9]]++;

        for (int k = 1; k <= 9; k++)
        {
            if (vi[k] != 1)
            {
                ok = 0;
            }
        }
    }

    cout << ok << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}