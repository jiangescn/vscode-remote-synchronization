#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> yinshu(int x)
{
    vector<int> ans;
    if (x > 0)
    {
        for (int i = 1; i * i <= x; i++)
        {
            if (x % i == 0)
            {
                if (x / i == i)
                {
                    ans.push_back(i);
                }
                else
                {
                    ans.push_back(i);
                    ans.push_back(x / i);
                }
            }
        }
        for (int i = -1; i * i <= x; i--)
        {
            if (x % i == 0)
            {
                if (x / i == i)
                {
                    ans.push_back(i);
                }
                else
                {
                    ans.push_back(i);
                    ans.push_back(x / i);
                }
            }
        }
    }
    else
    {
        for (int i = 1; i * i <= -x; i++)
        {
            if (x % i == 0)
            {
                ans.push_back(i);
                ans.push_back(-i);
                ans.push_back(x / i);
                ans.push_back(-x / i);
            }
        }
    }
    return ans;
}

void solve()
{
    int a, b, c;
    cin >> a >> b >> c;

    vector<int> aa = yinshu(a);
    vector<int> cc = yinshu(c);

    if (c != 0)
    {
        for (int i = 0; i < aa.size(); i++)
        {
            for (int j = 0; j < cc.size(); j++)
            {
                int a1 = aa[i];
                int a2 = a / a1;

                int b1 = cc[j];
                int b2 = c / b1;

                if (a1 * b2 + a2 * b1 == b)
                {
                    cout << a1 << " " << b1 << " " << a2 << " " << b2 << endl;
                    return;
                }
            }
        }
    }

    if (c == 0)
    {
        cout << a << " " << b << " " << 1 << " " << 0 << endl;
        return;
    }

    cout << "NO" << endl;
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