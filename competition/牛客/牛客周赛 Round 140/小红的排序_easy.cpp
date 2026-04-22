#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    int a, b;
    cin >> a >> b;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    int x = __gcd(a, b);
    if(a > n / 2 || b > n / 2)
    {
        x = min({a, b, abs(a - b)});
    }



    for (int i = 1; i <= n; i++)
    {
        if(s[i] == i)continue;

        while(s[i] != i)
        {
            if (abs(s[i] - i) % x != 0)
            {
                cout << "No" << endl;
                return;
            }

            swap(s[i], s[s[i]]);
        }
    }

    cout << "Yes" << endl;
    return;
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