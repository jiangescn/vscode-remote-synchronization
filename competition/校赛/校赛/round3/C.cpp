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

    vector<int> seam(n + 1);
    int val = 1;
    seam[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if(s[i] == s[i - 1])
        {
            seam[i] = val;
        }
        else
        {
            val = i;
            seam[i] = val;
        }
    }

    // for (int i = 1; i <= n; i++)
    // {
    //     cout << seam[i] << " ";
    // }cout << endl;

    int q;
    cin >> q;
    while(q--)
    {
        int l, r;
        cin >> l >> r;

        if (seam[r] <= l)
        {
            cout << "-1 -1" << endl;
        }
        else
        {
            cout << seam[r] - 1 << " " << seam[r] << endl;
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