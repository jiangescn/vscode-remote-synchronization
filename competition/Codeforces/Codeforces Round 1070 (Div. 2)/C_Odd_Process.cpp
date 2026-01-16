#include <bits/stdc++.h>
using namespace std;
#define int long long

bool cmp(int a, int b)
{
    return a > b;
}

void solv()
{
    int n;
    cin >> n;
    vector<int> even;
    vector<int> odd;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        sum += a;
        if (a & 1)
            odd.push_back(a);
        else
            even.push_back(a);
    }
    sort(even.begin(), even.end(), cmp);
    sort(odd.begin(), odd.end(), cmp);

    if (odd.empty())
    {
        for (int i = 0; i < n; i++)
        {
            cout << 0 << " ";
        }
        cout << endl;
    }
    else if (even.empty())
    {
        for (int i = 0; i < n; i++)
        {
            if (i & 1)
            {
                cout << 0 << " ";
            }
            else
            {
                cout << odd[0] << " ";
            }
        }
        cout << endl;
    }
    else
    {
        vector<int> ans(n);
        ans[0] = odd[0];
        for (int i = 0; i < n - 1; i++)
        {
            if (i < even.size())
                ans[i + 1] = ans[i] + even[i];
            else
                ans[i + 1] = ans[i - 1];
        }

        if(sum % 2 == 0)
        {
            ans[n - 1] = 0;
        }

        for (int i = 0; i < n; i++)
        {
            cout << ans[i] << " ";
        }
        cout << endl;
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
        solv();
    }
    return 0;
}