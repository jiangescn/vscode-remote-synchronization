#include <iostream>
using namespace std;

int main(void)
{
    int n;
    cin >> n;
    int data[200]={0};

    for (int i = 0; i < n; i++)
    {
        cin >> data[i];
    }

    int sum[20001]={0};
    int k = 0;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            k =data[i]+data[j];
            sum[k] = 1;
        }
    }
    
    int count = 0;
    for (int j = 0; j < n; j++) 
    {
        if (sum[data[j]] == 1) 
        { 
            count++;
        }
    }
    
    cout<<count<<endl;
    
    return 0;
    
}