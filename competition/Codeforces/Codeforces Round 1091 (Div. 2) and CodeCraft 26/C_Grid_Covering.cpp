#include <bits/stdc++.h>
using namespace std;
#define int long long

bool isPrime(int n)
{
    if (n <= 1)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;

    for (int i = 3; i <= sqrt(n); i += 2)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

void solve(){
    int n, m, a, b;
    cin >> n >> m >> a >> b;

    if(a == 1)
    {
        if(b == 1)
        {
            cout << "YES" << endl;
            return;
        }
    }

    if(isPrime(n % a) && isPrime(m % b))
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }

    // cout << 985865 % 899368 << endl;

}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}