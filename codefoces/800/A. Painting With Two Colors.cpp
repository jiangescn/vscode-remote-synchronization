#include <iostream>
using namespace std;

int main ()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n, a, b;
        cin >> n >> a >> b;

        if(n % 2 == 0)//一共偶数个空
        {
            if(b >= a && b % 2 == 0)
            {
                cout << "YES" << endl;
                continue;
            }
            if(a % 2 == 0 && b % 2 == 0)
            {
                cout << "YES" << endl;
                continue;
            }
        }
        else //一共奇数个空
        {
            if (b >= a && b % 2 == 1)
            {
                cout << "YES" << endl;
                continue;
            }
            if (a % 2 == 1 && b % 2 == 1)
            {
                cout << "YES" << endl;
                continue;
            }
        }
        cout << "NO" << endl;
    }
}