#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int x, y, p1, p2;
    cin >> x >> y >> p1 >> p2;

    if(x > y)
    {
        cout << "A" << endl;
    }
    else if(y > x)
    {
        cout << "B" << endl;
    }
    else
    {
        if(p1 > p2)
        {
            cout << "B" << endl;
        }
        else if(p2 > p1)
        {
            cout << "A" << endl;
        }
        else
        {
            cout << "C" << endl;
        }
    }
    return 0;
}