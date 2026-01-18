#include <iostream>
using namespace std;

int main (void)
{
    int o;
    cin >> o;
    for (int i = 0; i < o; i++)
    {
        int n;
        cin >> n;

        int count = 0;

        int data[2000]={0};
        for (int i = 0; i < n; i++)
        {
            int a;
            cin >> a;
            data[a]++;
        }
        for (int i = 0; i < 2000; i++)
        {
            if(data[i])count++;
        }
        
        cout<<2*count-1<<endl;
        
    }
    return 0;
    
}