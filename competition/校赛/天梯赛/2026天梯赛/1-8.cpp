#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    while (n--)
    {
        int op;
        cin >> op;

        if (op == 1)
        {
            string tar;
            cin >> tar;
            int time = 3;
            int pos = s.find(tar);

            int found = 0;
            while (time-- && pos != -1)
            {
                if (found != 0)
                    cout << " ";
                cout << pos;
                pos = s.find(tar, pos + 1);
                found++;
            }

            if (found == 0)
            {
                cout << -1;
            }

            cout << endl;
        }
        else if (op == 2)
        {
            int pos;
            string tar;
            cin >> pos >> tar;
            s.insert(pos, tar);
            cout << s << endl;
        }
        else if (op == 3)
        {
            int l, r;
            cin >> l >> r;

            if(l == r)
            {
                cout << s << endl;
                continue;
            }

            string t = s.substr(l, r - l + 1);
            reverse(t.rbegin(), t.rend());
            s.replace(l, r - l + 1, t);
            cout << s << endl;
        }
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