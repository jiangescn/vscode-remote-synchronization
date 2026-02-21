#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <string>
using namespace std;
#define int long long
// const int N = 998244353;
const long long mod = 1e9 + 7;
const int N = 200005;
int fac[N + 1], invfac[N + 1];
int qpow(int a, int b)
{
    int r = 1;
    while (b)
    {
        if (b & 1)
            r = r * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return r;
}

void init()
{
    fac[0] = 1;
    for (int i = 1; i <= N; i++)
        fac[i] = fac[i - 1] * i % mod;

    invfac[N] = qpow(fac[N], mod - 2);
    for (int i = N; i > 0; i--)
        invfac[i - 1] = invfac[i] * i % mod;
}

int C(int n, int k)
{
    if (k < 0 || k > n)
        return 0;
    return fac[n] * invfac[k] % mod * invfac[n - k] % mod;
}

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

bool isLeapYear(int year)
{
    if (year % 400 == 0)
    {
        return true;
    }
    else if (year % 100 == 0)
    {
        return false;
    }
    else if (year % 4 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

string add(string a, string b)
{
    int len = max(a.size(), b.size()), plus = 0;
    string ans = "";
    while (a.size() < len)
        a = '0' + a;
    while (b.size() < len)
        b = '0' + b;
    for (int i = len - 1; i >= 0; i--)
    {
        int temp1 = a[i] - '0', temp2 = b[i] - '0';
        int temp = temp1 + temp2 + plus;
        plus = temp / 10;
        temp %= 10;
        char ch = temp + '0';
        ans = ch + ans;
    }
    if (plus != 0)
        return '1' + ans;
    return ans;
}

string mtp(string la, string lb)
{
    int lena = la.size(), lenb = lb.size();
    int len = lena + lenb;
    vector<int> a(lena + 1), b(lenb + 1), c(len + 1);

    for (int i = 1; i <= lena; i++)
        a[i] = (la[lena - i] - '0');
    for (int i = 1; i <= lenb; i++)
        b[i] = (lb[lenb - i] - '0');

    for (int i = 1; i <= lenb; i++)
    {
        for (int j = 1; j <= lena; j++)
        {
            c[i + j - 1] += a[j] * b[i];
        }
    }

    for (int i = 1; i < len; i++)
    {
        c[i + 1] += c[i] / 10;
        c[i] %= 10;
    }

    while (c[len] == 0 && len > 1)
        len--;

    string ans;
    for (int i = len; i >= 1; i--)
    {
        ans += char(c[i] + '0');
    }
    return ans;
}

signed main()
{
    int a;
    cin >> a;
    cout << a;

    return 0;
}