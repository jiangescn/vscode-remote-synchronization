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
        string a;
        cin >> a;
        int m;
        cin >> m;
        string b, c;
        cin >> b;
        cin >> c;

        for (int i = m - 1; i >= 0; i--)
        {
            if(c[i] == 'V')cout << b[i];
        }
        cout << a;
        for (int i = 0; i < m; i++)
        {
            if(c[i] == 'D')cout << b[i];
        }
        cout << endl;
    }
}