#include <iostream>
#include <cmath>
using namespace std;

int block[200][200] = {0};

int main(void)
{
    int n , m, o;
    cin>> n >> m >> o;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            block[i][j]=1;
        }
    }


    for (int k = 0; k < m; k++)
    {
        int a,b;
        cin >> a >> b;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int dis = abs(a-1-i) + abs(b-1-j);
                if(dis <= 2)block[i][j]=0;
            }
        }
    }



    for (int k = 0; k < o; k++)
    {
        int a,b;
        cin >> a >> b;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int disa = abs(a-1-i);
                int disb = abs(b-1-j);
                if(disa<=2&&disb<=2)block[i][j]=0;
            }
        }
    }

    int count = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(block[i][j])count++;
        }
        
    }
    

    cout<<count<<endl;
    
    return 0;
}