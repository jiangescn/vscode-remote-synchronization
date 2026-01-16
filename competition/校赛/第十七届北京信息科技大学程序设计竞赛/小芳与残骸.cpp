#include <iostream>
#include <vector>
using namespace std;
#define int long long
const int N = 998244353;

int ksm(int a, int b)
{
    int ans = 1;
    while(b)
    {
        if(b & 1)
        {
            ans = ans * a % N;
        }
        a = a * a % N;
        b >>= 1;
    }
    return ans % N;
}

signed main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        cout << ksm(2, n - 1) << endl;
    }
}