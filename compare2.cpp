#include <bits/stdc++.h>
using namespace std;
#define int long long

struct SegTree
{
    int n;
    vector<int> tr;

    SegTree(int n = 0) : n(n)
    {
        tr.assign(4 * n + 10, 0);
    }

    void add(int i, int l, int r, int x, int v)
    {
        if (l == r)
        {
            tr[i] += v;
            return;
        }

        int mid = (l + r) >> 1;

        if (x <= mid)
            add(i << 1, l, mid, x, v);
        else
            add(i << 1 | 1, mid + 1, r, x, v);

        tr[i] = tr[i << 1] + tr[i << 1 | 1];
    }

    int query(int i, int l, int r, int jobl, int jobr)
    {
        if (jobl <= l && r <= jobr)
            return tr[i];

        int mid = (l + r) >> 1;
        int res = 0;

        if (jobl <= mid)
            res += query(i << 1, l, mid, jobl, jobr);

        if (jobr > mid)
            res += query(i << 1 | 1, mid + 1, r, jobl, jobr);

        return res;
    }

    void add(int x, int v)
    {
        add(1, 1, n, x, v);
    }

    int query(int l, int r)
    {
        if (l > r)
            return 0;

        return query(1, 1, n, l, r);
    }
};

int get_parity(vector<int> a, int n)
{
    SegTree seg(n);

    int res = 0;

    for (int i = 0; i < a.size(); i++)
    {
        int x = a[i];

        int greater = seg.query(x + 1, n);

        res ^= (greater & 1);

        seg.add(x, 1);
    }

    return res;
}

vector<int> build(vector<int> odd, vector<int> even, int n)
{
    vector<int> ans(n + 1);

    int p1 = 0, p2 = 0;

    for (int i = 1; i <= n; i++)
    {
        if (i & 1)
            ans[i] = odd[p1++];
        else
            ans[i] = even[p2++];
    }

    return ans;
}

void solve()
{
    int n;
    cin >> n;

    vector<int> a(n + 1);
    vector<int> odd, even;

    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];

        if (i & 1)
            odd.push_back(a[i]);
        else
            even.push_back(a[i]);
    }

    int p1 = get_parity(odd, n);
    int p2 = get_parity(even, n);

    sort(odd.begin(), odd.end());
    sort(even.begin(), even.end());

    vector<int> ans;

    if (p1 == p2)
    {
        ans = build(odd, even, n);
    }
    else
    {
        vector<int> odd1 = odd, even1 = even;
        vector<int> odd2 = odd, even2 = even;

        swap(odd1[odd1.size() - 1], odd1[odd1.size() - 2]);
        swap(even2[even2.size() - 1], even2[even2.size() - 2]);

        vector<int> ans1 = build(odd1, even1, n);
        vector<int> ans2 = build(odd2, even2, n);

        ans = min(ans1, ans2);
    }

    for (int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    cout << "\n";
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--)
        solve();

    return 0;
}