#include <bits/stdc++.h>
using namespace std;
#define int long long

int maxg(int x)
{
    int r = x / 2;
    if (x % 2 == 0)
    {
        r--;
    }
    return r;
}

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    map<int, int> vi;

    vector<int> bian(1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        if (s[i] > n || vi[s[i]])
        {
            bian.push_back(s[i]);
        }
        vi[s[i]] = 1;
    }

    vector<int> need(1);
    for (int i = 1; i <= n; i++)
    {
        if (!vi[i])
        {
            need.push_back(i);
        }
    }

    // for (int i = 1; i < bian.size(); i++)
    // {
    //     cout << bian[i] << " ";
    // }
    // cout << endl;
    // for (int i = 1; i < need.size(); i++)
    // {
    //     cout << need[i] << " ";
    // }
    // cout << endl;

    for (int i = 1; i < bian.size(); i++)
    {
        bian[i] = maxg(bian[i]);
    }
    sort(bian.begin() + 1, bian.end());

    // for (int i = 1; i < bian.size(); i++)
    // {
    //     cout << bian[i] << " ";
    // }
    // cout << endl;

    for (int i = 1; i < bian.size(); i++)
    {
        if (bian[i] < need[i])
        {
            cout << -1 << endl;
            return;
        }
    }

    // vector<int> ss = s;
    // for (int i = 1; i <= n; i++)
    // {
    //     if(ss[i] > i)
    //     {
    //         ss[i] = maxg(ss[i]);
    //     }
    // }
    // // sort(ss.begin() + 1, ss.end());

    // // for (int i = 1; i <= n; i++)
    // // {
    // //     cout << ss[i] << " ";
    // // }cout << endl;

    // for (int i = 1; i <= n; i++)
    // {
    //     if (ss[i] < i)
    //     {
    //         cout << -1 << endl;
    //         return;
    //     }
    // }

    cout << bian.size() - 1 << endl;
    return;
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