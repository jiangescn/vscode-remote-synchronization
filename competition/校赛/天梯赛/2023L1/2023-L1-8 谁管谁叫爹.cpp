#include <bits/stdc++.h>
using namespace std;
#define int long long

int digsum(int x)
{
    int sum = 0;
    while (x)
    {
        sum += x % 10;
        x /= 10;
    }
    return sum;
}

void solve()
{
    int na, nb;
    cin >> na >> nb;

    int sa = digsum(na);
    int sb = digsum(nb);

    int ans = 0;

    if (na % sb == 0)
    {
        ans += 1;
    }
    if(nb % sa == 0)
    {
        ans += 2;
    }

    if(ans == 1)
    {
        cout << "A" << endl;
    }
    else if(ans == 2)
    {
        cout << "B" << endl;
    }
    else
    {
        if(na > nb)
        {
            cout << "A" << endl;
        }
        else
        {
            cout << "B" << endl;
        }
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