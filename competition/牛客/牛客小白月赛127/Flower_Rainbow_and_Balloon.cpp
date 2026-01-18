#include <bits/stdc++.h>
using namespace std;
#define int long long
string s;
int n, m, k;

bool check(int x)
{
    int r = 0, y = 0, w = 0;
    int tar = 0;
    for(int i = 0; i < x; i++)
    {
        if(s[i] == 'r')
        {
            r++;
        }
        else if(s[i] == 'w')
        {
            w++;
        }
        else if(s[i] == 'y')
        {
            y++;
        }
    }
    tar = max(tar, max(r * 2 + y, y * 2 + r) + min(w, m) * 2);

    for (int i = x; i < n; i++)
    {
        if (s[i] == 'r')
        {
            r++;
        }
        else if (s[i] == 'w')
        {
            w++;
        }
        else if (s[i] == 'y')
        {
            y++;
        }


        if (s[i - x] == 'r')
        {
            r--;
        }
        else if (s[i - x] == 'w')
        {
            w--;
        }
        else if (s[i - x] == 'y')
        {
            y--;
        }
        tar = max(tar, max(r * 2 + y, y * 2 + r) + min(w, m) * 2);
    }
    return tar >= k;
}

void solve()
{
    cin >> n >> m >> k;
    cin >> s;

    int l = 1, r = n, ans = -1;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (check(mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    cout << ans << '\n';
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