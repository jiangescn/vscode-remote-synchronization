#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(2 * n + 1);
    int pos1 = -1, pos2 = -1;
    for (int i = 1; i <= 2 * n; i++)
    {
        cin >> s[i];
        if(s[i] == 0)
        if(pos1 == -1)
        {
            pos1 = i;
        }
        else
        {
            pos2 = i;
        }
    }

    // cout << pos1 << " " << pos2 << endl;

    auto check = [&](auto check, int pos) -> int{
        int l = pos, r = pos;
        set<int> st;
        while(s[l] == s[r])
        {
            st.insert(s[l]);
            l--;
            r++;
            if (l < 1) break;
            if (r > 2 * n) break;
        }
        int ans = -1;
        for (auto it : st)
        {
            if(it != ans + 1)
            {
                break;
            }
            ans = it;
        }
        return ans;
    };

    int ans = max(check(check, pos1), check(check, pos2));

    int l = pos1, r = pos2;
    set<int> st;

    while (l <= r && s[l] == s[r])
    {
        st.insert(s[l]);
        l++;
        r--;
    }

    if (l > r)
    {
        l = pos1 - 1;
        r = pos2 + 1;

        while (l >= 1 && r <= 2 * n && s[l] == s[r])
        {
            st.insert(s[l]);
            l--;
            r++;
        }

        int temp = -1;
        for (auto it : st)
        {
            if (it != temp + 1)
            {
                break;
            }
            temp = it;
        }

        ans = max(ans, temp);
    }
    cout << ans + 1 << endl;
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