#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;

        if (l2 < l1 && r1 < r2 || l1 < l2 && r2 < r1)
        {
            cout << "A" << endl;
        }
        else if (r1 < l2 || l1 > r2)
        {
            cout << "B" << endl;
        }
        else
        {
            cout << "C" << endl;
        }
    }
    return 0;
}