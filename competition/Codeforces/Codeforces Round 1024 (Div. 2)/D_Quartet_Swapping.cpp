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

    // x 要修改的位置
    // v 要加上的值
    void add(int i, int l, int r, int x, int v)
    {
        if (l == r)
        {
            tr[i] += v;
            return;
        }

        int mid = (l + r) >> 1;

        if (x <= mid)
        {
            add(i << 1, l, mid, x, v);
        }
        else
        {
            add(i << 1 | 1, mid + 1, r, x, v);
        }

        tr[i] = tr[i << 1] + tr[i << 1 | 1];
    }

    int query(int i, int l, int r, int jobl, int jobr)
    {
        if (jobl <= l && r <= jobr)
        {
            return tr[i];
        }

        int mid = (l + r) >> 1;
        int ans = 0;

        if (jobl <= mid)
        {
            ans += query(i << 1, l, mid, jobl, jobr);
        }

        if (jobr > mid)
        {
            ans += query(i << 1 | 1, mid + 1, r, jobl, jobr);
        }

        return ans;
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

int get_parity(vector<int> s, int n)
{
    SegTree seg(n);

    int ans = 0;

    for (int i = 0; i < s.size(); i++)
    {
        int x = s[i];

        int greater = seg.query(x + 1, n);

        ans ^= (greater & 1);

        seg.add(x, 1);
    }

    return ans;
}

vector<int> build(vector<int> odd, vector<int> even, int n)
{
    vector<int> ans(n + 1);

    int p1 = 0, p2 = 0;

    for (int i = 1; i <= n; i++)
    {
        if (i & 1)
        {
            ans[i] = odd[p1++];
        }
        else
        {
            ans[i] = even[p2++];
        }
    }

    return ans;
}

void solve()
{
    int n;
    cin >> n;

    vector<int> s(n + 1);
    vector<int> odd, even;

    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];

        if (i & 1)
        {
            odd.push_back(s[i]);
        }
        else
        {
            even.push_back(s[i]);
        }
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
    {
        cout << ans[i] << " \n"[i == n];
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}