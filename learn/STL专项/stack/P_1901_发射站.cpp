#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1E6 + 10;

void solv()
{
    int n;
    cin >> n;
    stack<int> st;
    vector<int> sum(n), h(n), v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> h[i] >> v[i];

        while (!st.empty() && h[st.top()] < h[i])
        {
            sum[i] += v[st.top()];
            st.pop();
        }

        if (!st.empty() && h[st.top()] > h[i])
        {
            sum[st.top()] += v[i];
        }

        st.push(i);
    }

    cout << *max_element(sum.begin(), sum.end()) << endl;
}

signed main()
{
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solv();
    }
    return 0;
}