#include <bits/stdc++.h>
using namespace std;
// #define int long long

void solve()
{
    int n, x;
    cin >> n >> x;
    vector<multiset<int>> s(n);
    for (int i = 0; i < x; i++)
    {
        int a, b;
        cin >> a >> b;
        s[a].insert(b);
        s[b].insert(a);
    }

    vector<int> vi(n);

    stack<int> st;
    for (int i = 0; i < n; i++)
    {
        vector<int> ansdfs;
        if (vi[i])
            continue;

        st.push(i);
        while (!st.empty())
        {
            int a = st.top();
            st.pop();

            if (vi[a]) continue;
            vi[a] = 1;
            ansdfs.push_back(a);

            for (auto it = s[a].rbegin(); it != s[a].rend(); ++it)
            {
                if (!vi[*it])
                    st.push(*it);
            }
        }

        cout << "{ ";
        for (int j = 0; j < ansdfs.size(); j++)
        {
            cout << ansdfs[j] << " ";
        }
        cout << "}" << '\n';
    }

    fill(vi.begin(), vi.end(), 0);
    queue<int> q;
    for (int i = 0; i < n; i++)
    {
        vector<int> ansbfs;
        if (vi[i])
            continue;

        q.push(i);
        vi[i] = 1;
        while (!q.empty())
        {
            int a = q.front();
            q.pop();
            ansbfs.push_back(a);
            for (auto it : s[a])
            {
                if (vi[it])
                    continue;
                q.push(it);
                vi[it] = 1;
            }
        }

        cout << "{ ";
        for (int i = 0; i < ansbfs.size(); i++)
        {
            cout << ansbfs[i] << " ";
        }
        cout << "}" << endl;
    }
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