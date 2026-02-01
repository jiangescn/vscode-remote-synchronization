#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 3010;
char s[N][N];
bool Break[N];

void dfs(int x, int y, int n)
{
    if (s[x][y] == '*')
        return;
    if (x < 1 || x > n || y < 1 || y > n)
        return;
    s[x][y] = '*';

    if (s[x - 1][y - 1] == '.')
        dfs(x - 1, y - 1, n);
    if (s[x - 1][y] == '.')
        dfs(x - 1, y, n);
    if (s[x - 1][y + 1] == '.')
        dfs(x - 1, y + 1, n);

    if (s[x - 1][y - 1] == '#' && Break[y - 1])
        dfs(x - 1, y - 1, n);
    if (s[x - 1][y] == '#' && Break[y])
        dfs(x - 1, y, n);
    if (s[x - 1][y + 1] == '#' && Break[y + 1])
        dfs(x - 1, y + 1, n);
}

void solve()
{
    int n, c;
    cin >> n >> c;
    memset(Break, 0, sizeof(Break));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> s[i][j];

    for (int i = 1; i + c <= n; i++)
    {
        int cbrk = 1;
        for (int j = n - i + 1; j <= n; j++)
        {
            if (s[j][i + c] == '#')
            {
                cbrk = 0;
                break;
            }
        }

        if (cbrk)
        {
            Break[i + c] = true;
        }
    }
    for (int i = 0; i + c >= 1; i--)
    {
        int cbrk = 1;
        for (int j = n + i + 1; j <= n; j++)
        {
            if (s[j][i + c] == '#')
            {
                cbrk = 0;
                break;
            }
        }
        if (cbrk)
        {
            Break[i + c] = true;
        }
    }

    // for (int i = 1; i <= n; i++)
    // {
    //     if(brk[i])
    //         cout << 'o';
    //     else
    //         cout << 'x';
    // }
    // cout << endl;

    dfs(n, c, n);

    // cout << "---------------" << endl;
    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = 1; j <= n; j++)
    //     {
    //         cout << s[i][j];
    //     }
    //     cout << endl;
    // }
    // cout << "---------------" << endl;

    for (int i = 1; i <= n; i++)
    {
        if (s[1][i] == '*')
        {
            cout << 1;
        }
        else
        {
            cout << 0;
        }
    }
    cout << '\n';
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
