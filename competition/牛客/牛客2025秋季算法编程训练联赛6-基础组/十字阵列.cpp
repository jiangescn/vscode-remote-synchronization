#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 1E9 + 7;
int s[2020][2020];
int shu[2020][2020];
int hen[2020][2020];

signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, h;
    cin >> n >> m >> h;

    for (int i = 1; i <= h; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        hen[a][1] += c;
        // hen[x[i]][m + 1]--;

        shu[1][b] += c;
        // shu[n + 1][y[i]]--;
        s[a][b] -= c;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            hen[i][j] += hen[i][j - 1];
        }
    }

    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = 1; j <= m; j++)
    //     {
    //         cout << hen[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // cout << endl;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            shu[i][j] += shu[i - 1][j];
            s[i][j] += hen[i][j] + shu[i][j];
        }
    }

    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = 1; j <= m; j++)
    //     {
    //         cout << s[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // cout << endl;

    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = 1; j <= m; j++)
    //     {
    //         cout << s[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    int sum = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            sum += s[i][j] * (i + j);
            sum %= N;
        }
    }

    cout << sum << endl;

    return 0;
}