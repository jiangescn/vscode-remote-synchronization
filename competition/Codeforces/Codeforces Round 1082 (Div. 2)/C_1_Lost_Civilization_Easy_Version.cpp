#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    stack<int> st;
    int ans = 1;
    st.push(s[1]);
    for (int i = 2; i <= n; i++)
    {
        while(st.size() && s[i] != st.top() + 1)
        {
            st.pop();
        }
        if(st.empty())
        {
            ans++;
        }
        st.push(s[i]);
    }

    cout << ans << endl;

}

// lda
// ida

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