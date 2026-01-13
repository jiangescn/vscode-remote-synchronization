#include <iostream>
using namespace std;
#define int long long

int ksm(int a, int b, int mod)
{
    int ans = 1;
    while(b)
    {
        if(b&1)
        {
            ans = ans * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return ans % mod;
}

signed main()
{
    int a, b, c;
    cin >> a >> b >> c;

    int ans = ksm(a, b, c);
    printf("%d^%d mod %d=%d", a, b, c, ans);
    return 0;
}