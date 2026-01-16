#include <bits/stdc++.h>
using namespace std;
#define int long long

void solv()
{
    int n;
    cin >> n;
    vector<int> s(n);
    unordered_set<int> st;
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
        st.insert(s[i]);
    }
    sort(s.begin(), s.end());
    int diff = st.size();

    int ans = *lower_bound(s.begin(), s.end(), diff);
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
        solv();
    }
    return 0;
}