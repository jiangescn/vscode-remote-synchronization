#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void pardon(vector<vector<int>>& squ, int x, int y, int size)
{
    if(size == 1)
    {
        return;
    }

    int half = size / 2;

    for (int i = x; i < x + half; i++)
    {
        for (int j = y; j < y + half; j++)
        {
            squ[i][j] = 0;
        }
        
    }

    pardon(squ, x, y + half, half);//右上
    pardon(squ, x + half, y, half);//左下
    pardon(squ, x + half, y + half, half);//右下
    
}

int main()
{
    int n;
    cin >> n;

    int size = pow(2, n);
    vector<vector<int>> squ(size, vector<int>(size, 1));

    pardon(squ, 0, 0, size);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if(j != 0) cout << " ";
            cout << squ[i][j];
        }
        cout << endl;
    }
    return 0;
}