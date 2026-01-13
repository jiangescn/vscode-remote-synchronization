#include <bits/stdc++.h>
using namespace std;
#define int long long

void solv()
{
    int n;
    cin >> n;
    vector<int> s(n);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
    }

    if(n == 1)
    {
        cout << 0 << endl;
        return;
    }

    int l = 0, r = 1;
    int ans = 0;
    while(l < n && r < n)
    {
        if(s[l] <= s[r])
        {
            l = r;
            r++;
        }
        else if(s[l] > s[r])
        {
            ans++;
            r++;
        }
    }
    cout << ans << endl;
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
        solv();
    }
    return 0;
}