#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, c, k;
    cin >> n >> c >> k;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    sort(s.begin() + 1, s.end());

    for (int i = 1; i <= n; i++)
    {
        if(c >= s[i] + 1 && k > 0)
        {
            int Max = min(c - s[i], k);

            k -= Max;
            c += Max + s[i];
        }
        else if(c >= s[i])
        {
            c += s[i];
        }
        else
        {
            break;
        }
    }

    cout << c << endl;
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