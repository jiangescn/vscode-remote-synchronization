#include <iostream>
using namespace std;

int main()
{
    int a, b, c, n;
    cin >> a >> b >> c >> n;
    int ans = a * n;
    if(n <= b)
    {
        ans -= c;
    }
    cout << ans << endl;
}