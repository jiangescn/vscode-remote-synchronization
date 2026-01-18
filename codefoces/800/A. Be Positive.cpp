#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main ()
{
    int o;
    cin >> o;
    for (int l = 0; l < o; l++)
    {
        int n;
        cin >> n;

        int product = 1;
        int count_zero = 0;

        for (int i = 0; i < n; i++)
        {
            int a;
            cin >> a;

            if(a == 0)count_zero++;
            else product *= a;
        }
        
        if(product > 0)cout << count_zero << endl;
        else cout << count_zero + 2 << endl;

    }
    return 0;
}