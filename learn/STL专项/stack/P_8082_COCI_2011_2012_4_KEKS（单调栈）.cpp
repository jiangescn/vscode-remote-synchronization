#include <bits/stdc++.h>
using namespace std;
#define int long long

void solv()
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    stack<int> st;

    for (int i = 0; i < n; i++)
    {
        if(st.empty() || s[st.top()] > s[i] || k == 0)
        {
            st.push(i);
        }
        else
        {
            while (!st.empty() && s[st.top()] < s[i])
            {
                st.pop();
                k--;
                if(!k)
                {
                    break;
                }
            }
            st.push(i);
        }
    }

    stack<int> ans;
    while(!st.empty())
    {
        ans.push(st.top()); st.pop();
    }
    while(!ans.empty())
    {
        cout << s[ans.top()]; ans.pop();
    }
    
    

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