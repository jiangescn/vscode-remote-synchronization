#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <queue>
#include <stack>
using namespace std;
#define int long long
// const int N = 998244353;

// 分解质因数
vector<pair<long long, int>> fct(int n)
{
    vector<pair<long long, int>> res;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            int cnt = 0;
            while (n % i == 0)
            {
                n /= i;
                cnt++;
            }
            res.push_back({i, cnt});
        }
    }
    if (n > 1)
        res.push_back({n, 1});
    return res;
}

//快速幂
const int mod = 1e9 + 7;
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

int inv(int x)
{
    return qpow(x, mod - 2) % mod;
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

// 线性筛（欧拉筛）
const int N = 1000000;
bool vis[N + 5];
int primes[N + 5], tot;
void sieve(int n)
{
    fill(vis + 1, vis + n + 1, false);
    vis[1] = true;
    tot = 0;
    for (int i = 2; i <= n; i++)
    {
        if (!vis[i])
            primes[++tot] = i;
        for (int j = 1; j <= tot && 1LL * i * primes[j] <= n; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}


// 等差数列
int sum_arithmetic_mod(int a1, int d, int n)
{
    int x = (2 * a1 % mod + (n - 1) % mod * d % mod) % mod;
    if (x % 2 == 0) return n % mod * (x / 2 % mod) % mod;
    else return (n / 2 % mod) * x % mod;
}
// 等比数列
int sum_geometric(int a1, int r, int n)
{
    if (r == 1) return a1 % mod * (n % mod) % mod;
    int numerator = (qpow(r, n) - 1 + mod) % mod;
    int denominator = inv(r - 1);
    return a1 % mod * numerator % mod * denominator % mod;
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

// KMP
vector<int> getNext(const string &p)
{
    int n = p.size();
    vector<int> ne(n, 0);
    for (int i = 1, j = 0; i < n; i++)
    {
        while (j > 0 && p[i] != p[j])
            j = ne[j - 1];
        if (p[i] == p[j])
            j++;
        ne[i] = j;
    }
    return ne;
}
vector<int> kmp(const string &s, const string &p)
{
    vector<int> ne = getNext(p), pos;
    for (int i = 0, j = 0; i < (int)s.size(); i++)
    {
        while (j > 0 && s[i] != p[j])
            j = ne[j - 1];
        if (s[i] == p[j])
            j++;
        if (j == (int)p.size())
        {
            pos.push_back(i - j + 1);
            j = ne[j - 1];
        }
    }
    return pos;
}

// 拓扑排序
vector<int> topoSort(int n, vector<vector<int>> &e)
{
    vector<int> indeg(n + 1, 0), topo;
    for (int u = 1; u <= n; u++)
    {
        for (int v : e[u])
            indeg[v]++;
    }
    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        if (indeg[i] == 0)
            q.push(i);
    }
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        topo.push_back(u);
        for (int v : e[u])
        {
            if (--indeg[v] == 0)
                q.push(v);
        }
    }
    if ((int)topo.size() != n)
        return {};
    return topo;
}

void solve()
{
    // 排序去重
    vector<int> a;
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());

    // 背包
    // 01
    vector<int> dp, w, v;
    int n;
    int m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = m; j >= w[i]; j--)
        {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    // 完全
    for (int i = 1; i <= n; i++)
    {
        for (int j = w[i]; j <= m; j++)
        {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }

    // string:
    string s = "abcd";
    s.insert(2, "XYZ");
    cout << s; // abXYZcd

    string s = "abcd";
    s.insert(1, 3, '*');
    cout << s; // a***bcd

    string s = "abcdef";
    s.erase(2, 3);
    cout << s; // abf

    string s = "abcdef";
    s.erase(s.begin() + 1, s.begin() + 4);
    cout << s; // aef

    string s = "abcdef";
    s.replace(2, 3, "XYZ");
    cout << s; // abXYZf

    string s = "abcdef";
    cout << s.substr(2, 3); // cde

    string s = "abcabc";
    cout << s.find("bc"); // 1

    string s = "abcabc";
    cout << s.find("bc", 2); // 4
    if (s.find("xyz") == string::npos)
    {
        cout << "not found\n";
    }

    string s = "abcdef";
    reverse(s.begin(), s.end());
    cout << s; // fedcba

    string s = "AbCd";
    for (char &c : s)
        c = tolower(c);
    cout << s; // abcd

    int x = 123;
    string s = to_string(x); // "123"

    string s = "456";
    int x = stoi(s);
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}