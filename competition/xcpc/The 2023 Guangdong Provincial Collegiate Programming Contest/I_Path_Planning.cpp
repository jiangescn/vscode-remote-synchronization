#include <bits/stdc++.h>
using namespace std;

struct Point
{
    int x, y;
};

const int N = 1e6 + 5;
Point a[N];

void solve()
{
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int val;
            scanf("%d", &val);
            a[val] = {i, j};
        }
    }

    if (n == 1 || m == 1)
    {
        printf("%d\n", n * m);
        return;
    }

    set<pair<int, int>> st;

    for (int i = 0; i < n * m; i++)
    {
        int x = a[i].x;
        int y = a[i].y;

        auto it = st.lower_bound({x, y});

        if (it != st.end() && (it->second) < y)
        {
            printf("%d\n", i);
            return;
        }

        if (it != st.begin())
        {
            auto pre = prev(it);
            if (pre->second > y)
            {
                printf("%d\n", i);
                return;
            }
        }

        st.insert({x, y});
    }

    printf("%d\n", n * m);
}

int main()
{
    int _;
    scanf("%d", &_);
    while (_--)
    {
        solve();
    }
    return 0;
}

// 按x排序后，y 单调不降