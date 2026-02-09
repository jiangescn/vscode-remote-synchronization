#include <bits/stdc++.h>
using namespace std;
#define int long long

// method 1
int cont(vector<int>& s)
{
    int mx = 0, cur = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i]) cur++;
        else cur--;
        cur = max(cur, 0ll);
        mx = max(cur, mx);
    }
    int mn = 0; cur = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i]) cur++;
        else cur--;
        cur = min(cur, 0ll);
        mn = min(mn, cur);
    }
    return max(mx, abs(mn));
}

// method 2
// int cont(vector<int>& s)
// {
//     stack<int> st;
//     int count = 0;
//     for (int i = 0; i < s.size(); i++)
//     {
//         if (st.empty())
//         {
//             st.push(s[i]);
//         }
//         else
//         {
//             count++;
//             while((!st.empty()) && (s[i] != st.top()))
//             {
//                 s[i] = st.top();
//                 st.pop();
//             }
//         }
//     }
//     return count + st.size();
// }
// 大 失 败 ！

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    int ok = 1;
    for (int i = 1; i < n; ++i)
        if (s[i] == s[i - 1])
        {
            ok = 0;
            break;
        }

    if (ok)
    {
        cout << 0 << '\n';
        return;
    }

    vector<int> mA;
    vector<int> mB;
    for (int i = 0; i < n; ++i)
    {
        int t = s[i] - '0';
        if (t != (i & 1))
            mA.push_back(t);
        if (t == (i & 1))
            mB.push_back(t);
    }

    int ans = LLONG_MAX;
    // cout << "    mA:" << endl;
    // for (int i = 0; i < mA.size(); i++)
    // {
    //     cout << mA[i] << " ";
    // }cout << endl;
    // cout << "    mB:" << endl;
    // for (int i = 0; i < mB.size(); i++)
    // {
    //     cout << mB[i] << " ";
    // }cout << endl;
    ans = min(ans, cont(mA));
    ans = min(ans, cont(mB));

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