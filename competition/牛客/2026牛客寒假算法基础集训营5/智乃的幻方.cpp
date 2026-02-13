#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int s[10][10] = {0};
    int count[10] = {0};
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            cin >> s[i][j];
            count[s[i][j]]++;
        }
    }

    for (int i = 1; i <= 9; i++)
    {
        if (count[i] == 0)
        {
            cout << "No" << endl;
            return;
        }
    }

    set<int> st;
    for (int i = 1; i <= 3; i++)
    {
        int sum = 0;
        for (int j = 1; j <= 3; j++)
        {
            sum += s[i][j];
        }
        st.insert(sum);
    }
    for (int i = 1; i <= 3; i++)
    {
        int sum = 0;
        for (int j = 1; j <= 3; j++)
        {
            sum += s[j][i];
        }
        st.insert(sum);
    }
    if(st.size() != 1)
    {
        // for (auto it : st)
        // {
        //     cout << it << " ";
        // }
        // cout << endl;
        cout << "No" << endl;
        return;
    }

    st.insert(s[1][1] + s[2][2] + s[3][3]);
    st.insert(s[3][1] + s[2][2] + s[1][3]);

    if (st.size() != 1)
    {
        // for (auto it : st)
        // {
        //     cout << it << " ";
        // }
        // cout << endl;
        cout << "No" << endl;
        return;
    }

    cout << "Yes" << endl;

    // for (auto it: st)
    // {
    //     cout << it << " ";
    // }cout << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}