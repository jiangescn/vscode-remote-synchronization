#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, q;
    cin >> n >> q;

    vector<int> tar;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        tar.push_back(x);
    }

    deque<int> st;
    deque<int> qu;
    vector<int> a, b;

    while(q--)
    {
        int op;
        cin >> op;
        if(op == 1)
        {
            int x;
            cin >> x;
            st.push_back(x);
            qu.push_back(x);
        }
        else
        {

            a.push_back(st.back());
            st.pop_back();
            b.push_back(qu.front());
            qu.pop_front();
        }
    }

    // for (auto it : st)
    // {
    //     a.push_back(it);
    // }
    // for (auto it : qu)
    // {
    //     b.push_back(it);
    // }

    int idx = 0;
    if(tar == a)
    {
        idx += 1;
    }
    if(tar == b)
    {
        idx += 2;
    }

    if(idx == 3)
    {
        cout << "both" << endl;
        return;
    }
    else if(idx == 1)
    {
        cout << "stack" << endl;
        return;
    }
    else if(idx == 2)
    {
        cout << "queue" << endl;
        return;
    }

    cout << -1 << endl;
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