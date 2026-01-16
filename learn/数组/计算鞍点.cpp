#include <iostream>
using namespace std;

int main (void)
{
    int data[5][5]={0};
    int found = 0;
    
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cin >> data[i][j];
        }
    }

    for (int i = 0; i < 5; i++)
    {
        int max = data[i][0];
        int max_y = 0;
        for (int j = 0; j < 5; j++)
        {
            if(data[i][j] > max)
            {
                max=data[i][j];
                max_y = j;
            }
        }


        int min = data[0][max_y];
        for (int k = 0; k < 5; k++)
        {
            if (data[k][max_y] < min)
            {
                min=data[k][max_y];
            }
        }
        
        if (max == min)
        {
            cout << i + 1 << " " << max_y + 1 << " " << max << endl;
            found = 1;
            break; 
        }

    }
    
    if(!found)cout<<"not found"<<endl;
    return 0;
}