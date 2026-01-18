#include <bits/stdc++.h>
using namespace std;
#define int long long

void solv()
{
    int n;
    cin >> n;
    vector<int> s;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        s.push_back(a);
    }
    s.push_back(-1);

    stack<int> st;
    int ans = 0;
    for (int i = 0; i <= n; i++)
    {
        while(!st.empty() && s[st.top()] > s[i])
        {
            int height = s[st.top()];
            st.pop();

            int width = st.empty() ? i : i - st.top() - 1;

            ans = max(ans, height * width);
        }
        st.push(i);
    }
    
    cout << ans << endl;
    return;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solv();
    }
    return 0;
}