#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s;
    while(n != 0)
    {
        s.push_back(n % 10);
        n /= 10;
    }
    reverse(s.begin(), s.end());
    sort(s.begin() + 1, s.end());

    // for (int i = 0; i < s.size(); i++)
    // {
    //     cout << s[i] << " ";
    // }cout << endl;

    int sum = 0;
    int i;
    for (i = 0; i < s.size(); i++)
    {
        if(sum + s[i] >= 10)
        {
            break;
        }
        sum += s[i];
    }

    int ans = s.size() - i;

    sum = 0;
    s[0] = 1;
    for (i = 0; i < s.size(); i++)
    {
        if (sum + s[i] >= 10)
        {
            break;
        }
        sum += s[i];
    }
    ans = min(ans, (int)s.size() - i + 1);

    // cout << s.size() << " " << i << endl;
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