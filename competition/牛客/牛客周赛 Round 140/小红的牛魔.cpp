#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    string st;
    for (char c : s)
    {
        st.push_back(c);

        if (st.size() >= 3 && st.substr(st.size() - 3) == "niu")
        {
            st.erase(st.size() - 3);
        }
        else if (st.size() >= 2 && st.substr(st.size() - 2) == "mo")
        {
            st.erase(st.size() - 2);
        }
    }

    if (st.empty())
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}