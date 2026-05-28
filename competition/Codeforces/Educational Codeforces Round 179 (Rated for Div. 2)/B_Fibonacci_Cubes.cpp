#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 2e5 + 10;
vector<int> s;

void solve()
{
    int n, q;
    cin >> n >> q;

    int tar = s[n];
    int tar2 = s[n - 1] + s[n];
    // cout << tar << " " << tar2 << endl;

    while (q--)
    {
        int a, b, c;
        cin >> a >> b >> c;

        int Max = max({a, b, c});
        int Min = min({a, b, c});

        if (Max >= tar2 && Min >= tar)
        {
            cout << 1;
        }
        else
        {
            cout << 0;
        }
    }
    cout << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    s.push_back(0);
    s.push_back(1);
    s.push_back(2);

    int a = 1, b = 2;
    while (a + b <= N)
    {
        b = a + b;
        a = b - a;
        s.push_back(b);
    }

    // for (int i = 1; i <= 20; i++)
    // {
    //     cout << s[i] << " ";
    // }

    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}