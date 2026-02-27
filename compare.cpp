#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MAXV = 1000000; // 状态上界（包含）

int re(int x)
{
    int r = 0;
    while (x > 0)
    {
        r = r * 10 + (x % 10);
        x /= 10;
    }
    return r;
}

// 全局静态数组用时间戳法避免每组测试 memset
static vector<int> seen(MAXV + 1, 0);
static vector<int> deep(MAXV + 1, 0);

void solve()
{
    int a = 2;
    cout << a << endl;
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