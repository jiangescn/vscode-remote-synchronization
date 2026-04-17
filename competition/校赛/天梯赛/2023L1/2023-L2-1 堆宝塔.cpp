#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    stack<int> a;
    stack<int> b;
    int ans = 0;
    int Max = 0;
    for (int i = 1; i <= n; i++)
    {
        if (a.empty())
        {
            a.push(s[i]);
            continue;
        }

        if (s[i] < a.top())
        {
            a.push(s[i]);
            continue;
        }

        if (b.empty())
        {
            b.push(s[i]);
            continue;
        }

        if (s[i] > b.top())
        {
            b.push(s[i]);
            continue;
        }

        Max = max(Max, (long long)a.size());
        Max = max(Max, (long long)b.size());
        while (!a.empty())
        {
            // cout << a.top() << " ";
            a.pop();
        }
        // cout << endl;
        while (!b.empty() && s[i] < b.top())
        {
            a.push(b.top());
            b.pop();
        }

        a.push(s[i]);

        ans++;
        Max = max(Max, (long long)a.size());
        Max = max(Max, (long long)b.size());
    }

    ans += !a.empty();
    ans += !b.empty();

    Max = max(Max, (long long)a.size());
    Max = max(Max, (long long)b.size());

    cout << ans << " ";
    cout << Max << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}