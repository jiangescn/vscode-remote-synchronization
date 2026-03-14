#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, o;
    cin >> n >> o;
    vector<int> s(n);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
    }
    while (o--)
    {
        int op;
        cin >> op;
        // cerr << "op = " << op << endl;

        if (op == 1)
        {
            int x, y;
            cin >> x;
            vector<int> yuan(x);
            for (int i = 0; i < x; i++)
                cin >> yuan[i];
            cin >> y;
            vector<int> xin(y);
            for (int i = 0; i < y; i++)
                cin >> xin[i];

            auto it = search(s.begin(), s.end(), yuan.begin(), yuan.end());
            if (it != s.end())
            {
                int pos = it - s.begin();
                s.erase(s.begin() + pos, s.begin() + pos + yuan.size());
                s.insert(s.begin() + pos, xin.begin(), xin.end());
            }
        }
        if (op == 2)
        {
            int m = s.size();
            if (m <= 1) continue;
            vector<int> b;
            for (int i = 0; i < m - 1; ++i)
            {
                b.push_back(s[i]);
                if ((s[i] + s[i + 1]) % 2 == 0)
                {
                    b.push_back((s[i] + s[i + 1]) / 2);
                }
            }
            b.push_back(s[m - 1]);
            s.swap(b);
        }
        if (op == 3)
        {
            int l, r;
            cin >> l >> r;
            reverse(s.begin() + l - 1, s.begin() + r);
        }
    }

    for (int i = 0; i < s.size(); i++)
    {
        if (i != 0)
        {
            cout << " ";
        }
        cout << s[i];
    }
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