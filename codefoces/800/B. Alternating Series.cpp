#include <iostream>
using namespace std;

int main ()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;

        for (int i = 0; i < n - 1; i++)
        {
            if(i != 0)cout << " ";
            if(i % 2)
            {
                cout << "3";
            }
            else 
            {
                cout << "-1";
            }
        }
        
        if (n % 2 == 0)cout << " 2";
        else cout << " -1";

        cout << endl;
    }
    return 0;
}