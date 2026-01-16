#include <iostream>
#include <vector>
using namespace std;


int main()
{
    int a, b;
    cin >> a >> b;
    int dx[] = {1, 1, 0, 0, -1, -1, 1, -1};
    int dy[] = {1, 0, 1, -1, 0, 1, -1, -1};

    int s[200][200] = {0};
    char c;
    for (int i = 1; i <= a; i++)
    {
        for (int j = 1; j <= b; j++)
        {
            cin >> c;
            if(c == '*')
            {
                for (int k = 0; k < 8; k++)
                {
                    s[i + dx[k]][j + dy[k]]++;
                }
                s[i][j] = -9999999;
            }
        }
    }

    for (int i = 1; i <= a; i++)
    {
        for (int j = 1; j <= b; j++)
        {
            if(s[i][j] >= 0)
            {
                cout << s[i][j];
            }
            else
            {
                cout << "*";
            }
        }
        cout << endl;
    }
    
    
}