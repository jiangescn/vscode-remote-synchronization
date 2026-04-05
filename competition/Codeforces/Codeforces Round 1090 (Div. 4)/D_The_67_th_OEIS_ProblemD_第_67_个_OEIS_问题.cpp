#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e6 + 10;
vector<int> isp(N + 1, 1);
vector<int> prim;

void solve()
{
    int n;
    cin >> n;

    vector<int> s(n + 1);

    if (n == 2)
    {
        cout << "2 2" << endl;
        return;
    }

    
    s[1] = prim[0];
    for (int i = 2; i <= n - 1; i++)
    {
        s[i] = prim[i - 2] * prim[i - 1];
    }
    s[n] = prim[n - 2];

    for (int i = 1; i <= n; i++)
    {
        cout << s[i] << " ";
    }
    cout << endl;
    return;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    isp[0] = 0, isp[1] = 0;
    for (int i = 2; i * i <= N; i++)
    {
        if (isp[i])
        {
            for (int j = i * i; j <= N; j += i)
            {
                isp[j] = 0;
            }
        }
    }

    for (int i = 2; i <= N; i++)
    {
        if (isp[i])
        {
            prim.push_back(i);
        }
    }

    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}