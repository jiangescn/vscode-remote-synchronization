#include <iostream>
#include <vector>
using namespace std;

int s[200][200];

int main()
{
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> s[i][j];
            s[i][j] += s[i][j - 1] + s[i - 1][j] - s[i - 1][j - 1];
        }        
    }


    int ans = 1;
    
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if(s[i][j] - s[i][j-ans] - s[i-ans][j] + s[i-ans][j-ans] == ans * ans) ans++;
        }
    }
    cout << ans - 1 << endl;
    return 0;
}