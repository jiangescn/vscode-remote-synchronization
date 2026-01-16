#include <bits/stdc++.h>
using namespace std;

char s[4000][4000] = {0};
int vi[4000][4000];
int h, w;

int mox[5] = {0, 1, -1, 0};
int moy[5] = {1, 0, 0, -1};

int ans = INT_MAX;

void dfs(int x, int y, int stp)
{
    //cout << '(' << x << "," << y << ')' << "stp:" << stp << endl;
    vi[x][y] = 1;

    if (s[x][y] == 'T')
    {
        ans = min(ans, stp);
        //cout << "End" << endl;
        //return;
    }

    for (int i = 0; i < 4; i++)
    {
        int xx = x + mox[i];
        int yy = y + moy[i];

        if (s[xx][yy] == 'M')
        {
            xx += mox[i];
            yy += moy[i];
        }

        if (xx > h || xx < 1 || yy > w || yy < 1 || s[xx][yy] == '#' || vi[xx][yy] == 1)
            continue;
        //vi[xx][yy] = 1;
        dfs(xx, yy, stp + 1);
        //vi[xx][yy] = 0;
    }
    return;
}

int main()
{
    cin >> h >> w;
    int mx, my;

    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= w; j++)
        {
            cin >> s[i][j];
            if (s[i][j] == 'S')
            {
                mx = i;
                my = j;
                // cout << "!!" << endl;
            }
        }
    }

    // cout << "m: (" << mx << "," << my << ')' << endl;
    dfs(mx, my, 0);

    if(ans == INT_MAX)
    {
        cout << -1 << endl;
        return 0;
    }
    cout << ans << endl;
    return 0;
}