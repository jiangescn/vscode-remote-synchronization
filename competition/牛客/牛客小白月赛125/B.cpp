#include <bits/stdc++.h>
using namespace std;
#define int long long

void solv()
{
    int n, q;
    cin >> n >> q;
    vector<int> s;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        s.push_back(a);
    }

    for (int o = 0; o < q; o++)
    {
        int k, x;
        cin >> k >> x;

        int l = 0, r = n;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (s[mid] >= x)
            {
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }

        //cout << l << endl;
        if(l >= k)
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
}

signed main()
{
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solv();
    }
    return 0;
}