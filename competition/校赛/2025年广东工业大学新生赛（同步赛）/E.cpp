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

signed main()
{
    for (int i = 1; i < 10000; i++)
    {
        if(isPrime(i))
        {
            cout << i << endl;
        }
    }
    
}