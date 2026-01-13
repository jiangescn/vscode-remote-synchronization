#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        int n, q;
        cin >> n >> q;
        vector<int> s;
        map<int, bool> va;
        for (int i = 1; i <= n; i++)
        {
            int a;
            cin >> a;
            va[a] = true;
            if (a != 1)
                s.push_back(a);
        }
        n = s.size();

        // for (int i = 0; i < n; i++)
        // {
        //     cout << s[i] <<" ";
        // }cout << endl;

        for (int i = 0; i < n; i++)
        {
            int mtp = 1;
            for (int j = i; j < n && mtp <= 1e9; j++)
            {
                mtp *= s[j];
                va[mtp] = true;
            }
        }
    
        for (int i = 0; i < q; i++)
        {
            int x;
            cin >> x;
            cout << (va[x] ? "Yes" : "No") << endl;
        }
    }
}