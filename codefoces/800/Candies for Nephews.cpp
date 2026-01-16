#include <iostream>
using namespace std;

int main ()
{
    int t;
    cin >> t;
    while(t--)
    {
        int a;
        cin >> a;
        int count = 0;

        while(a%3!=0)
        {
            a++;
            count ++;
        }
        
        cout << count << endl;
    }
    return 0;
}