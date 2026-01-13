#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1E6 + 10;
vector<int> s(N);
vector<int> h(N);

void solve()
{
    int a, b;
    cin >> a >> b;

    int cas1 = min(s[min(a, b)], h[max(a, b)]);
    int cas2 = min(s[max(a, b)], h[min(a, b)]);

    cout << max(cas1, cas2) + 1 << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int count = 0;
    int tpow = 2;
    for (int i = 1; i <= N; i++)
    {
        if (i < tpow)
        {
            s[i] = count;
        }
        else
        {
            count += 2;
            tpow += pow(2, count + 1);
            s[i] = count;
        }
    }

    count = 0;
    tpow = 1;
    for (int i = 1; i <= N; i++)
    {
        if (i < tpow)
        {
            h[i] = count - 1;
        }
        else
        {
            count += 2;
            tpow += pow(2, count);
            h[i] = count - 1;
        }
    }
    // for (int i = 1; i <= 100 ;i++)
    // {
    //     cout << s[i] << " ";
    // }
    // cout << endl;

    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}