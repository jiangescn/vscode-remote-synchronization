#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<int> s(n + 1);
    map<int, int> count;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        count[s[i]]++;
    }

    // sort(s.begin() + 1, s.end());
    // for (int i = 1; i <= n; i++)
    // {
    //     cout << s[i] << " ";
    // }cout << endl;

    int seam = INT_MAX;
    int kong = INT_MAX;
    for (int i = n; i >= 0; i--)
    {
        if(count[i] == 0)
        {
            kong = i;
        }
        if(count[i] > 1)
        {
            seam = i;
        }
    }

    int ans = 0;
    int op = 0;
    if(kong < seam) op = 1;

    // cout << "kong: " << kong << endl;

    if(k == 1)
    {
        for (int i = 0; i <= n; i++)
        {
            if(count[i] == 0) continue;

            if(i < kong)
            {
                if(count[i] == 1)
                {
                    ans += i;
                }
                else
                {
                    ans += count[i] * (kong);
                }
            }
            else
            {
                ans += count[i] * kong;
            }
        }

        cout << ans << endl;
        return;
    }


    int t = 0;
    for (int i = 0; i <= n; i++)
    {
        if (count[i] == 0)
            continue;

        if (i < min(kong, seam))
        {
            ans += i;
        }
        else
        {
            t += count[i];
        }
    }


    if (op)
    {
        if (t == 1)
        {
            ans += t * kong;
        }
        else
        {
            if (k & 1) ans += t * kong;
            else ans += t * (kong + 1);
        }
        cout << ans << endl;
        return;
    }

    if(k & 1) ans += t * (min(kong, seam) + 1);
    else ans += t * (min(kong, seam));

    cout << ans << endl;
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