#include <iostream>
#include <cmath>
using namespace std;

int main ()
{
    int t;
    cin >> t;
    while (t--)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        int mx = max(a, b);
        int mn = min(a, b);

        if((mx - 1) / 2 > mn)
        {
            cout << "NO" << endl;
            continue;
        }

        mx = max(c - a, d - b);
        mn = min(c - a, d - b);

        if ((mx - 1) / 2 > mn)
        {
            cout << "NO" << endl;
            continue;
        }

        cout << "YES" << endl;
    }
}