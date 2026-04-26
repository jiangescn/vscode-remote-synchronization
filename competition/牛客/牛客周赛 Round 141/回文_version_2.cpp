#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    string s;
    cin >> s;
    int n = s.size();

    // cout << n << endl;

    if (n == 1)
    {
        cout << "YES" << endl;
        return;
    }

    if (n == 2)
    {
        if (s[0] == s[1])
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
        return;
    }

    s = " " + s;

    int l = 1, r = n;

    while (abs(l - r) > 2)
    {
        if (s[l] == s[r])
        {
            l++;
            r--;
        }
        else if (s[l] != s[r])
        {
            if (s[l] == 'm')
            {
                if(s[r - 1] != 'n')
                {
                    cout << "NO" << endl;
                    return;
                }
                l++;
                r -= 2;
            }
            else if (s[r] == 'm')
            {
                if(s[l + 1] != 'n')
                {
                    cout << "NO" << endl;
                    return;
                }
                l += 2;
                r--;
            }
        }

        // cout << "L:" << l << "  R:" << r << endl;
    }

    if (abs(l - r) == 2)
    {
        if (s[l + 1] == 'n')
        {
            cout << "YES" << endl;
            return;
        }
        else if (s[l] == s[r])
        {
            cout << "YES" << endl;
            return;
        }
        else
        {
            cout << "NO" << endl;
            return;
        }
    }
    if (abs(l - r) == 1)
    {
        if (s[l] == s[r])
        {
            cout << "YES" << endl;
            return;
        }
        else
        {
            cout << "NO" << endl;
            return;
        }
    }
    else if (l == r)
    {
        cout << "YES" << endl;
        return;
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