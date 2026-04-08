#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    int sum = 0;
    vector<array<int, 2>> v(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> v[i][0] >> v[i][1];
        sum += v[i][1];
    }
    sort(v.begin() + 1, v.end());

    sum /= 2;

    int cur = 0;
    int t1 = 0;
    int idx = 1;
    while (idx <= n && cur <= sum)
    {
        if (cur + v[idx][1] > sum)
        {
            t1 += (sum - cur) * v[idx][0];
            v[idx][1] -= sum - cur;
            cur = sum;
            break;
        }
        t1 += v[idx][0] * v[idx][1];
        cur += v[idx][1];
        idx++;
    }

    cur = 0;
    int t2 = 0;
    idx = n;
    while (idx >= 1 && cur <= sum)
    {
        if (cur + v[idx][1] > sum)
        {
            t2 += (sum - cur) * v[idx][0];
            v[idx][1] -= sum - cur;
            cur = sum;
            break;
        }
        t2 += v[idx][0] * v[idx][1];
        cur += v[idx][1];
        idx--;
    }

    cout << t2 - t1 << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int _ = 1;
    cin >> _;
    while (_--)
    {
        solve();
    }
    return 0;
}