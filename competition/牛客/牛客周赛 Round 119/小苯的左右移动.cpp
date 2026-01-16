#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 998244353;

int ksm(int a, int b, int mod)
{
    int ans = 1;
    while(b)
    {
        if(b & 1)
        {
            ans = ans * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return ans % N;
}

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int a, k;
        cin >> a >> k;
        vector<int> s(a + 1, 0);

        int sum = 0;
        int mn = 0;
        for (int i = 0; i < a; i++)
        {
            cin >> s[i];
            i % 2 ? sum -= s[i] : sum += s[i];
            mn = min(mn, sum);
        }

        if (mn < 0)
        {
            int shift = -mn;
            if (shift < 60)
                k = (k >> shift) << shift;
            }
            else
            {
                k = 0;
            }
        

        if (sum > 0)
        {
            cout << (k * ksm(2, sum, N)) % N << endl;
        }
        else if(sum < 0)
        {
            int shift = -sum;
            if (shift < 60)
            {
                k = k >> shift;
            }
            else
            {
                k = 0;
            }
            cout << k % N << endl;
        }
        else
        {
            cout << k % N << endl;
        }
    }
}

