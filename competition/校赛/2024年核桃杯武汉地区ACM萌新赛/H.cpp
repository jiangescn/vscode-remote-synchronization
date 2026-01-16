#include <iostream>
using namespace std;
#define int long long

signed main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        if(n == 1)
        {
            cout << "-1" << " " << "-1" << endl;
            continue;
        }


        int b = n * (n + 1);
        int a = n + 1;

        cout << a << " " << b << endl;
    }
    return 0;
}