#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int aa, bb;
    cin >> aa >> bb;
    vector<int> a(aa + 1);
    vector<int> b(bb + 1);
    int suma = 0, sumb = 0;
    for (int i = 1; i <= aa; i++)
    {
        cin >> a[i];
        suma += a[i];
    }
    for (int i = 1; i <= bb; i++)
    {
        cin >> b[i];
        sumb += b[i];
    }

    sort(a.begin() + 1, a.end(), greater<int>());
    sort(b.begin() + 1, b.end(), greater<int>());

    if (suma == sumb)
    {
        cout << 1 << endl;
    }
    else if (suma > sumb)
    {
        int cha = suma - sumb;
        int count = 0;
        for (int i = 1; i <= aa; i++)
        {
            if (cha > 0)
            {
                cha -= a[i];
                count++;
            }
            else
            {
                break;
            }
        }

        cout << count << endl;
    }
    else
    {
        int cha = sumb - suma;
        int count = 0;
        for (int i = 1; i <= bb; i++)
        {
            if (cha > 0)
            {
                cha -= b[i];
                count++;
            }
            else
            {
                break;
            }
        }

        cout << count << endl;
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
        solve();
    }
    return 0;
}