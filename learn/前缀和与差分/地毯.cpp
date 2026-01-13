#include <iostream>
using namespace std;

int s[2010][2010];

int main()
{
    int m, n;
    cin >> m >> n;

    int x1, y1, x2, y2;

    for (int i = 1; i <= n; i++)
    {
        cin >> x1 >> y1 >> x2 >> y2;

        for (int x = x1; x <= x2; x++)
        {
            s[x][y1]++;
            s[x][y2+1]--;
        }
    }

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            s[i][j] += s[i][j-1];
        }        
    }
    
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if(j != 1)cout << " ";
            cout << s[i][j];
        }
        cout << endl;
    }
    
    return 0;
}