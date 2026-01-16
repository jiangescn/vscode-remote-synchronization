#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        if(n % 2)
        {
            for (int i = 0; i < n; i++)
            {
                cout << "a";
            }
            cout << endl;
            continue;
        }

        if(n == 2)
        {
            cout << "ab" << endl;
            continue;
        }

        cout << "aab";
        for (int i = 0; i < n - 3; i++)
        {
            cout << "a";
        }
        cout << endl;
        //cout << "----------------" << endl;
    }
}