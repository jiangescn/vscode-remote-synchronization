#include <iostream>
#include <vector>
using namespace std;
#define int long long
int m, n, a, b;
int s[500][500];

int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dy[] = {-1, 1, -2, 2, 2, -2, 1, -1};
bool cdt(int x, int y)
{
    if (x == a && y == b)
        return true;
    for (int i = 0; i < 8; i++)
        if(x == a + dx[i] && y == b + dy[i])
            return true;
    return false;
}

signed main()
{
    cin >> m >> n >> a >> b;
    for (int j = 0; j <= n; j++)
    {
        if(cdt(0, j))break;
        s[0][j] = 1;
    }
    for (int i = 0; i <= m; i++)
    {
        if(cdt(i, 0))break;
        s[i][0] = 1;
    }
    
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (cdt(i, j))continue;
            if (!cdt(i - 1, j))s[i][j] += s[i - 1][j];
            if (!cdt(i, j - 1))s[i][j] += s[i][j - 1];
        }
    }
    
    cout << s[m][n] << endl;
    return 0;
}