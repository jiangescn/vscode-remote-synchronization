#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    double n;
    cin >> n;
    if(n < 60)
    {
        cout << "0.00" << endl;
        return 0;
    }
    cout << fixed << setprecision(2) << (n - 60) * 0.1 + 1 << endl;
}