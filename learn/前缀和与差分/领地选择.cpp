#include <iostream>
#include <vector>
using namespace std;

int s[1010][1010];

int main()
{
    int n, m, c;
    cin >> n >> m >> c;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> s[i][j];
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            s[i][j] += s[i][j-1];
        }
    }
    for (int j = 1; j <= m; j++)
    {
        for (int i = 1; i <= n; i++)
        {
            s[i][j] += s[i-1][j];
        }
    }

    int Max = -1E9;
    int mx, my;
    for (int i = c; i <= n; i++)
    {
        for (int j = c; j <= m; j++)
        {
            int num = s[i][j] - s[i][j-c] - s[i-c][j] + s[i-c][j-c];
            if(num > Max)
            {
                Max = num;
                mx = i;
                my = j;
            }
        }
    }
    
    cout << mx - c + 1 << " " << my - c + 1 << endl;    
    return 0;
}