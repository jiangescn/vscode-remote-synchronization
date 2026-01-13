#include <bits/stdc++.h>
using namespace std;
#define int long long

void solv()
{
    int n;
    cin >> n;

    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    stack<int> st;
    vector<int> ans(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        if (st.empty() || s[i] < s[st.top()])
        {
            st.push(i);
        }
        else
        {
            while(!st.empty() && s[i] > s[st.top()])
            {
                ans[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
    }

    for (int i = 1; i <= n; i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;
}


signed main()
{
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solv();
    }
    return 0;
}