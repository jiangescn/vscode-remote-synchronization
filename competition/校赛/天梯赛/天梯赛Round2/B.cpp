#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    // cout << s << endl;
    deque<char> dq;
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        if (!dq.empty())
        {
            // cout << dq.back() << endl;
            if (dq.back() == s[i])
            {
                dq.pop_back();
                count++;
            }
            else
            {
                dq.push_back(s[i]);
            }
        }
        else
        {
            dq.push_back(s[i]);
        }

        // for (auto it: dq)
        // {
        //     cout << it << " ";
        // }
        // cout << endl;
    }

    while (dq.size() >= 2 && dq.front() == dq.back())
    {
        count++;
        dq.pop_back();
        dq.pop_front();
    }

    cout << count * 2 << endl;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int _ = 1;
    while (_--)
    {
        solve();
    }
    return 0;
}