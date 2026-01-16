#include <iostream>
#include <string>
using namespace std;

bool flower(int x)
{
    int a=x%10;
    int b=x/10%10;
    int c=x/100;
    int sum = a*a*a+b*b*b+c*c*c;
    if(sum == x)return true;
    else return false;
}

int main()
{
    int a,b;
    while(cin >> a >> b)
    {
        int count = 0;
        int first = 0;
        for (int i = a; i <= b; i++)
        {
            if(flower(i))
            {
                if(first)
                {
                    cout<<" ";
                
                }
                cout << i;
                first = 1;
            }
        }
        if(!first)cout<<"no"<<endl;
        }
    return 0;    
}