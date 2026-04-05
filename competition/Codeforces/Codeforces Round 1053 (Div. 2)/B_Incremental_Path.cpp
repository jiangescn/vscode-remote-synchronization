#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> s(m + 1);
    unordered_map<int, int> vi;
    string op;
    cin >> op;
    op = " " + op;
    for (int i = 1; i <= m; i++)
    {
        cin >> s[i];
        vi[s[i]] = 1;
    }

    int cur = 1;
    for (int i = 1; i < n; i++)
    {
        if(op[i] == 'A')
        {
            cur++;
            vi[cur] = 1;
            s.push_back(cur);
        }
        else if(op[i] == 'B')
        {
            while(vi[++cur]);
            s.push_back(cur);
            vi[cur] = 1;
            while (vi[++cur]);
        }
    }

    if (op[n] == 'A')
    {
        cur++;
        vi[cur] = 1;
        s.push_back(cur);
    }
    else if (op[n] == 'B')
    {
        while (vi[++cur]);
        s.push_back(cur);
        vi[cur] = 1;
    }

    s.push_back(cur);
    sort(s.begin() + 1, s.end());
    s.erase(unique(s.begin() + 1, s.end()), s.end());
    cout << s.size() - 1 << endl;
    for (int i = 1; i < s.size(); i++)
    {
        cout << s[i] << " ";
    }
    cout << endl;
    return;

}

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