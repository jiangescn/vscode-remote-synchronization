#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 2e5+10;
const int mod = 998244353;
vector<int> fa(N);

int find(int x)
{
    if(fa[x] == x) return x;
    else return fa[x] = find(fa[x]);
}

bool un(int a, int b)
{
    int x = find(a), y = find(b);
    if(x != y)
    {
        fa[x] = y;
        return true;
    }
    else
    {
        return false;
    }
}

int qpow(int a, int b)
{
    int r = 1;
    while(b)
    {
        if(b & 1) r = r * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return r % mod;
}

void solve()
{
    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++)
    {
        fa[i] = i;
    }
    while(k--)
    {
        int a, b;
        cin >> a >> b;
        un(a, b);
    }

    unordered_set<int> s;
    for (int i = 1; i <= n; i++)
    {
        s.insert(find(i));
    }

    cout << qpow(26, s.size()) << endl;

}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}