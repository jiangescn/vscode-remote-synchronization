#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;

    vector<int> s;
    while (n != 0)
    {
        s.push_back(n & 1);
        n >>= 1;
    }

    reverse(s.begin(), s.end());

    while (!s.empty() && s.back() == 0)
    {
        s.pop_back();
    }

    // for (int i = 0; i < s.size(); i++)
    // {
    //     cout << s[i] << " \n"[i == s.size() - 1];
    // }
    int count = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i])
        {
            count++;
        }
    }

    if (count & 1)
    {
        cout << "NO" << endl;
        return;
    }

    vector<int> temp = s;
    reverse(temp.begin(), temp.end());

    if (temp == s)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
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