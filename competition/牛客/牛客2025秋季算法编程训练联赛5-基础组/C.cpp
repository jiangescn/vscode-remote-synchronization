#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int n, r;
    cin >> n >> r;
    // double cosa = cos(3.1415926*2 / n) ;
    // cout << cosa << endl;

    double a = 2 * r * r * (1 - cos(3.141592653589793238462643 * 2 / n));
    //cout << sqrt(a) << endl;

    int i, j;
    cin >> i >> j;

    int Min = abs(i - j);
    Min = min(Min, abs(n - Min));

    cout << fixed << setprecision(10) <<  Min * sqrt(a) << endl;
}