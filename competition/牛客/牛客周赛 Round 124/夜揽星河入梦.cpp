#include <bits/stdc++.h>
using namespace std;
#define int long long

int sums(vector<int> ss)
{
    if(ss.size() == 0)
    {
        return 0;
    }
    int ans = 0;
    for (int i = 1; i < ss.size(); i++)
    {
        ans = max(ans, ss[i] + ss[i - 1] + 1);
    }
    return ans;
}

void solve()
{
    int n, k;
    cin >> n >> k;
    // if (n + 1 < k)
    // {
    //     cout << "NO" << endl;
    //     return;
    // }
    vector<int> s(n);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
    }
    sort(s.begin(), s.end());

    vector<int> ss;
    int count = 1;
    int ans = 0;
    int sspush = 0;
    for (int i = 1; i < n; i++)
    {
        if(s[i] - s[i-1] == 1)
        {
            count++;
        }
        else if(s[i] - s[i - 1] == 2)
        {
            ss.push_back(count);
            sspush = 1;
            count = 1;
        }
        else
        {
            ans = max(ans, count + 1);
            if(sspush) ss.push_back(count);
            ans = max(ans, sums(ss));

            ss.resize(0, 0);
            count = 1;
            sspush = 0;
        }
    }
    ans = max(ans, count + 1);
    if (sspush)
        ss.push_back(count);
    ans = max(ans, sums(ss));

    //cout << "   :" << ans << endl;

    if(ans >= k)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
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