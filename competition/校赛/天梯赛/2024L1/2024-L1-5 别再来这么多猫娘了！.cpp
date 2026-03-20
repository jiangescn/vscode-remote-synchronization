#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{

    int n;
    cin >> n;
    vector<string> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    int k;
    cin >> k;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string tar;
    getline(cin, tar);

    string ans;
    int cnt = 0;
    int m = tar.size();
    for (int i = 0; i < m;)
    {
        bool matched = false;
        for (int j = 1; j <= n; j++)
        {
            int len = s[j].size();
            if (i + len <= m && tar.compare(i, len, s[j]) == 0)
            {
                cnt++;
                ans += "<censored>";
                i += len;
                matched = true;
                break;
            }
        }

        if (!matched)
        {
            ans += tar[i];
            i++;
        }
    }

    if (cnt >= k)
    {
        cout << cnt << endl;
        cout << "He Xie Ni Quan Jia!" << endl;
    }
    else
    {
        cout << ans << endl;
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}