#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 10;
vector<int> fa(N);
vector<int> rankv(N);

// 普通并查集
int FindTimeOut(int x)
{
    if (fa[x] == x)
    {
        return x;
    }
    else
    {
        return FindTimeOut(fa[x]);
    }
}

void solveTimeOut()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        fa[i] = i;
    }
    for (int i = 1; i <= m; i++)
    {
        int op, x, y;
        cin >> op >> x >> y;
        x = FindTimeOut(x), y = FindTimeOut(y);
        if (op == 1)
        {
            fa[x] = y;
        }
        else
        {
            if (x == y)
            {
                cout << "Y" << endl;
            }
            else
            {
                cout << "N" << endl;
            }
        }
    }
}

// 路径压缩优化
int Find1(int x)
{
    if (fa[x] == x)
    {
        return x;
    }
    else
    {
        return fa[x] = Find1(fa[x]);
    }
}

void solve1()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        fa[i] = i;
    }
    for (int i = 1; i <= m; i++)
    {
        int op, x, y;
        cin >> op >> x >> y;
        x = Find1(x), y = Find1(y);
        if (op == 1)
        {
            fa[x] = y;
        }
        else
        {
            if (x == y)
            {
                cout << "Y" << endl;
            }
            else
            {
                cout << "N" << endl;
            }
        }
    }
}

// 按秩合并优化  按高度合并
int find2(int x)
{
    if (fa[x] == x)
    {
        return x;
    }
    else
    {
        return find2(fa[x]);
    }
}

void solve2()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        fa[i] = i;
        rankv[i] = 1;
    }

    for (int i = 1; i <= m; i++)
    {
        int op, x, y;
        cin >> op >> x >> y;
        x = find2(x), y = find2(y);
        if (op == 1)
        {
            if (rankv[x] > rankv[y])
            {
                swap(x, y);
            }
            if (rankv[x] == rankv[y])
            {
                rankv[y]++;
            }
            fa[x] = y;
        }
        else
        {
            if(x == y)
            {
                cout << "Y" << endl;
            }
            else
            {
                cout << "N" << endl;
            }
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve2();
    }
    return 0;
}