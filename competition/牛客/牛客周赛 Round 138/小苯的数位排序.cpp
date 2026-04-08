#include <bits/stdc++.h>
using namespace std;
#define int long long

int sumdig(int x)
{
    int sum = 0;
    while(x)
    {
        sum += x % 10;
        x /= 10;
    }
    return sum;
}

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    for (int i = n;  i>= 1; i--)
    {
        cin >> s[i];
    }

    int ans = 0;
    for (int i = 2; i <= n; i++)
    {
        while(s[i] > s[i - 1])
        {
            if(s[i] == sumdig(s[i]))
            {
                cout << -1 << endl;
                return;
            }
            s[i] = sumdig(s[i]);
            ans++;
        }
    }
    cout << ans << endl;
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