#include <bits/stdc++.h>
using namespace std;
#define int long long
#define itn int

void solve()
{
    int n, q;
    cin >> n >> q;

    vector<int> s(n + 1);
    vector<int> pos(n + 1);

    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        pos[s[i]] = i;
    }

    while (q--)
    {
        int l, r, k;
        cin >> l >> r >> k;

        int count = 0, sum = 0;
        int countt = 0, summ = 0;

        if (pos[k] < l || pos[k] > r)
        {
            cout << -1 << ' ';
            continue;
        }

        while (l <= r)
        {
            int mid = (l + r) >> 1;

            if (s[mid] == k)
            {
                break;
            }

            if (mid < pos[k])
            {
                l = mid + 1;

                if (s[mid] > k)
                {
                    countt++;
                }

                count++;
            }
            else
            {
                r = mid - 1;

                if (s[mid] < k)
                {
                    summ++;
                }

                sum++;
            }
        }

        if (count > k - 1 || sum > n - k)
        {
            cout << -1 << ' ';
        }
        else
        {
            cout << max(summ, countt) * 2 << ' ';
        }

    }

    cout << endl;
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