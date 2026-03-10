
#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    int ones = 0;
    vector<int> pos;
    pos.reserve(n);
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '1')
        {
            ones++;
            pos.push_back(i);
        }
    }


    //全为0
    if (pos.empty())
    {
        cout << (n + 2) / 3 << "\n";
        return;
    }


    int add = 0;

    //前端 00001....
    int lead = pos[0];
    add += (lead + 1) / 3;

    //中间 ...1000001...
    for (int i = 0; i + 1 < (int)pos.size(); i++)
    {
        int len = pos[i + 1] - pos[i] - 1;
        add += len / 3;
    }

    //末尾 ....1000
    int tail = n - (pos.back() + 1);
    add += (tail + 1) / 3;

    cout << ones + add << "\n";
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
