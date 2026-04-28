#include <bits/stdc++.h>
using namespace std;
#define int long long

int ask(const vector<int> &s)
{
    int n = s.size();
    cout << "? " << n;
    for (int i = 0; i < n; i++)
    {
        cout << " " << s[i];
    }
    cout << endl;
    int res;
    cin >> res;
    return res;
}

void solve()
{
    int n;
    cin >> n;

    vector<int> ans(2 * n + 1);

    vector<int> t;
    vector<int> tt;

    for (int i = 1; i <= 2 * n; i++)
    {
        vector<int> temp = t;
        temp.push_back(i);

        int res = ask(temp);
        if (res)
        {
            ans[i] = res;
            tt.push_back(i);
        }
        else
        {
            t.push_back(i);
        }
    }

    for (int i = 1; i <= 2 * n; i++)
    {
        if (ans[i] == 0)
        {
            vector<int> temp = tt;

            temp.push_back(i);
            int res = ask(temp);

            ans[i] = res;
        }
    }

    cout << "!";
    for (int i = 1; i <= 2 * n; i++)
    {
        cout << " " << ans[i];
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