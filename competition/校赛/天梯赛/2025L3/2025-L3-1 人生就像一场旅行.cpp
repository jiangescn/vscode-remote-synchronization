#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int l, n;
    cin >> l >> n;

    if (n == 2)
    {
        cout << l + 1 << endl;
        return;
    }

    if (n == 3)
    {
        int ans = 0;

        for (int a = 0; a <= l; a++)
            for (int b = 0; b <= l; b++)
                for (int c = 0; c <= l; c++)
                    for (int d = 0; d <= l; d++)
                    {
                        int e = l - a - b;
                        int f = l - c - d;
                        int g = l - a - c;
                        int h = l - b - d;

                        if (e < 0)
                            continue;
                        if (f < 0)
                            continue;
                        if (g < 0)
                            continue;
                        if (h < 0)
                            continue;

                        int i = l - e - f;
                        if (i < 0)
                            continue;

                        ans++;
                    }

        cout << ans << endl;
    }
    else if (n == 4)
    {
        int ans = 0;

        for (int a = 0; a <= l; a++)
            for (int b = 0; b <= l; b++)
                for (int c = 0; c <= l; c++)
                    for (int d = 0; d <= l; d++)
                        for (int e = 0; e <= l; e++)
                            for (int f = 0; f <= l; f++)
                                for (int g = 0; g <= l; g++)
                                    for (int h = 0; h <= l; h++)
                                        for (int i = 0; i <= l; i++)
                                        {
                                            int y1 = l - a - b - e;
                                            int y2 = l - c - d - f;
                                            int y3 = l - g - h - i;
                                            int x1 = l - a - c - g;
                                            int x2 = l - b - d - h;
                                            int x3 = l - e - f - i;

                                            if (y1 < 0 || y2 < 0 || y3 < 0)
                                                continue;
                                            if (x1 < 0 || x2 < 0 || x3 < 0)
                                                continue;

                                            int x = l - y1 - y2 - y3;
                                            if (x < 0)
                                                continue;
                                            ans++;
                                        }

        cout << ans << endl;
    }
}

signed main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}