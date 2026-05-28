#include <bits/stdc++.h>
using namespace std;

struct SegTree
{
    struct node
    {
        int l, r;
        int s, lz;
        bool tag;
    };

    int n;
    vector<int> a;
    vector<node> tr;

    SegTree(int n = 0) : n(n)
    {
        a.assign(n + 1, 1);
        tr.assign(4 * n + 10, {0, 0, 0, 0});
    }

    void push_up(int p)
    {
        tr[p].s = tr[p << 1].s + tr[p << 1 | 1].s;
    }

    void apply(int p, int t)
    {
        tr[p].s = (tr[p].r - tr[p].l + 1) * t;
        tr[p].lz = t;
        tr[p].tag = true;
    }

    void push_down(int p)
    {
        if (tr[p].tag)
        {
            apply(p << 1, tr[p].lz);
            apply(p << 1 | 1, tr[p].lz);
            tr[p].tag = false;
        }
    }

    void build(int p, int l, int r)
    {
        tr[p] = {l, r, 0, 0};
        if (l == r)
        {
            tr[p].s = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        push_up(p);
    }

    void modify(int p, int l, int r, int t)
    {
        if (l <= tr[p].l && tr[p].r <= r)
        {
            apply(p, t);
            return;
        }
        push_down(p);
        int mid = (tr[p].l + tr[p].r) >> 1;
        if (l <= mid)
            modify(p << 1, l, r, t);
        if (mid < r)
            modify(p << 1 | 1, l, r, t);
        push_up(p);
    }

    int query(int p, int l, int r)
    {
        if (l <= tr[p].l && tr[p].r <= r)
        {
            return tr[p].s;
        }
        int res = 0;
        push_down(p);
        int mid = (tr[p].l + tr[p].r) >> 1;
        if (l <= mid)
            res += query(p << 1, l, r);
        if (mid < r)
            res += query(p << 1 | 1, l, r);
        return res;
    }
};







#define int long long

const int N = 100001;
vector<int> arr(N + 1);
vector<int> sum(N << 2 + 1);
vector<int> add(N << 2 + 1);

// 累加和信息的汇总
void up(int i)
{
    //父累加和 = 左范围累加和 + 右范围累加和
    sum[i] = sum[i << 1] + sum[i << 1 | 1];
}

void lazy(int i, int val, int n)
{
    sum[i] += val * n;
    add[i] += val;
}

//懒标记的下发
void down(int i, int ln, int rn)
{
    if(add[i] != 0)
    {
        //发左
        lazy(i << 1, add[i], ln);
        //发右
        lazy(i << 1 | 1, add[i], rn);
        //父范围懒信息清空
        add[i] = 0;
    }

}

// 建树
void build(int l, int r, int i)
{
    if(l == r)
    {
        sum[i] = arr[l];
    }
    else
    {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
    add[i] = 0;
}

// 范围修改
// jobl ~ jobr范围上每个数字增加jobv
void Add(int jobl, int jobr, int jobv, int l, int r, int i)
{
    if(jobl <= l && jobr >= r)
    {
        lazy(i, jobv, r - l + 1);
    }
    else
    {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        if(jobl <= mid)
        {
            Add(jobl, jobr, jobv, l, mid, i << 1);
        }
        
        if(jobr > mid)
        {
            Add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

//查询累加和
int query(int jobl, int jobr, int l, int r, int i)
{
    if(jobl <= l && jobr >= r)
    {
        return sum[i];
    }
    
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);

    int ans = 0;
    if(jobl <= mid)
    {
        ans += query(jobl, jobr, l , mid, i << 1);
    }
    if(mid < jobr)
    {
        ans += query(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}


void solve()
{
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    build(1, n, 1);

    while(q--)
    {
        int op;
        cin >> op;
        if(op == 1)
        {
            int x, y, k;
            cin >> x >> y >> k;
            Add(x, y, k, 1, n, 1);
        }
        else if(op == 2)
        {
            int x, y;
            cin >> x >> y;
            int ans = query(x, y, 1, n, 1);
            cout << ans << endl;
        }
    }

}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _ = 1;
    // cin >> _;
    while(_--)
    {
        solve();
    }
}

