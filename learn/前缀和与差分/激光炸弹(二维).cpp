#include <iostream>
#include <vector>
using namespace std;

int s[5010][5010];

int main()
{
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        int x, y, v;
        cin >> x >> y >> v;

        s[x+1][y+1] += v;
    }

    int N = 5001;
    
    for (int i = 1; i <= N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            s[i][j] += s[i][j-1];
        }
    }

    for (int j = 1; j <= N; j++)
    {
        for (int i = 1; i <= N; i++)
        {
            s[i][j] += s[i-1][j];
        }   
    }

    int Max = 0;
    for (int i = m; i <= N; i++)
    {
        for (int j = m; j <= N; j++)
        {
            int num = s[i][j] - s[i - m][j] - s[i][j - m] + s[i - m][j - m];
            Max = max(Max, num);
        }
    }
    
    cout << Max << endl;
    return 0;   
}

