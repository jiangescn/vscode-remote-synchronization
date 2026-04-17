#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<array<int, 3>> s(n + 1);
    map<int, int> count;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i][0];
        s[i][1] = i;
        count[s[i][0]]++;
    }

    for (auto it : count)
    {
        if (it.second % it.first != 0)
        {
            cout << -1 << endl;
            return;
        }
    }

    int val = 1;
    int t = 0;
    sort(s.begin() + 1, s.end());

    for (int i = 1; i <= n; i++)
    {
        s[i][2] = val;
        t++;
        if(t == s[i][0])
        {
            t = 0;
            val++;
        }
    }
    sort(s.begin() + 1, s.end(), [&](array<int, 3> a, array<int, 3> b){
        return a[1] < b[1];
    });


    for (int i = 1; i <= n; i++)
    {
        cout << s[i][2] << " ";
    }
    cout << endl;
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