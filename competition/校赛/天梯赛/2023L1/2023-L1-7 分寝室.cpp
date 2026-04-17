#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int a, b, n;
    cin >> a >> b >> n;

    int ans[2] = {0};
    int Min = INT_MAX;

    for (int i = 1; i < n; i++)
    {
        if(a % i == 0)
        {
            if(b % (n - i) == 0)
            {
                if(a / i == 1 || b / (n - i) == 1)
                continue;
                if(abs(a/i - b/(n-i)) < Min)
                {
                    ans[0] = i;
                    ans[1] = n - i;
                    Min = abs(a / i - b / (n - i));
                }
            }
        }
    }

    if(ans[0] == 0 || ans[1] == 0)
    {
        cout << "No Solution" << endl;
        return;
    }
    else
    {
        cout << ans[0] << " " << ans[1] << endl;
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}