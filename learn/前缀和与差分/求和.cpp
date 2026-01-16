#include <iostream>
using namespace std;

#define int long long

signed main()
{
    int n;
    cin >> n;

    int sum = 0;
    int posum = 0;

    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        sum += a;
        posum += a*a;
    }

    int ans = (sum * sum - posum) / 2;

    cout << ans << endl;
    return 0;
}