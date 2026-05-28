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

    vector<int> ans;
    ans.push_back(1);
    int l = 2, r = n;
    int last = s[1];
    while (l < r)
    {
        if (last < s[l] && last < s[r])
        {
            if (s[l] > s[r])
            {
                ans.push_back(1);
                l++;
                ans.push_back(0);
                last = s[r];
                r--;
            }
            else
            {
                ans.push_back(0);
                r--;
                ans.push_back(1);
                last = s[l];
                l++;
            }
        }
        else if (last > s[l] && last > s[r])
        {
            if (s[l] < s[r])
            {
                ans.push_back(1);
                l++;
                ans.push_back(0);
                last = s[r];
                r--;
            }
            else
            {
                ans.push_back(0);
                r--;
                ans.push_back(1);
                last = s[l];
                l++;
            }
        }
        else
        {
            ans.push_back(0);
            r--;
            ans.push_back(1);
            last = s[l];
            l++;
        }
    }

    if (l == r)
    {
        ans.push_back(1);
    }

    for (auto it : ans)
    {
        if (it)
        {
            cout << "L";
        }
        else
        {
            cout << "R";
        }
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