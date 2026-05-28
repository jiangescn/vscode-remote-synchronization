#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 1e4;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> s(n + 1);
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        sum += s[i];
    }

    if (sum == k)
    {
        cout << 0 << endl;
        return;
    }

    if (sum < k)
    {
        k -= sum;
        sort(s.begin() + 1, s.end());
        for (int i = 1; i <= n; i++)
        {
            if (N - s[i] < k)
            {
                k -= N - s[i];
                // cout << "K:" << k << endl;
            }
            else
            {
                cout << i << endl;
                return;
            }
        }

        // cout << "ONE" << endl;
    }
    else
    {
        k -= sum;
        k *= -1;

        // cout << "K:" << k << endl;

        sort(s.begin() + 1, s.end(), greater<int>());
        for (int i = 1; i <= n; i++)
        {
            if (s[i] + N < k)
            {
                k -= s[i] + N;
                // cout << "K:" << k << endl;
            }
            else
            {
                cout << i << endl;
                return;
            }
        }

        // cout << "TWO" << endl;
    }
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