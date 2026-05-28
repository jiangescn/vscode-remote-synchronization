#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int a, b, n, s;
    cin >> a >> b >> n >> s;

    if ((s % a  != 0) || a > s)
    {
        cout << "YES" << '\n';
        for (int i = 1; i <= n; i++)
        {
            cout << a << " \n"[i == n];
        }
        return;
    }
    if ((s % b != 0) || b > s)
    {
        cout << "YES" << '\n';
        for (int i = 1; i <= n; i++)
        {
            cout << b << " \n"[i == n];
        }
        return;
    }

    if (a > b)
    {
        swap(a, b);
    }

    // a== b

    int cnta = s / a, cntb = s / b;

    if (2 * a != b && a != b)
    {
        int cn1 = n / (cntb);
        int cn2 = n % (cntb);

        cout << "YES" << '\n';
        for (int i = 1; i <= cn1; i++)
        {
            for (int j = 1; j <= cntb - 1; j++)
            {
                cout << b << ' ';
            }

            cout << a << ' ';
        }

        for (int i = 1; i <= cn2; i++)
        {
            cout << b << ' ';
        }

        cout << '\n';

        return;
    }

    if (n >= s / a)
    {
        cout << "NO" << '\n';
        return;
    }
    else
    {
        cout << "YES" << '\n';
        for (int i = 1; i <= n; i++)
        {
            cout << a << " \n"[i == n];
        }
        return;
    }
}

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int _ = 1;
    cin >> _;
    while (_--)
    {
        solve();
    }
    return 0;
}