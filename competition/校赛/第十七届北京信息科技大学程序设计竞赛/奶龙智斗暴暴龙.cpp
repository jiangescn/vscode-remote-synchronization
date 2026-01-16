#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    double n;
    cin >> n;

    double ans = 0.5 + (double)(n - 1) / (double)(2 * n - 1) / 2.0;
    cout << fixed << setprecision(6) << ans << endl;
}