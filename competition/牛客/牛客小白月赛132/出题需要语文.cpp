#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;

    vector<set<array<int, 2>>> s(7);
    for (int i = 1; i <= n; i++)
    {
        char ch;
        int x;
        cin >> ch >> x;
        if(x >= 60)
        {
            s[ch - 'A'].insert({x, i});
        }
    }

    for (int i = 0; i < 6; i++)
    {
        if(s[i].empty())
        {
            cout << -1 << endl;
            return;
        }
    }

    int sum = 0;
    for (int i = 0; i < 6; i++)
    {
        sum += (*s[i].rbegin())[0];
    }

    if(sum / 6 < 70)
    {
        cout << -1 << endl;
        return;
    }

    for (int i = 0; i < 6; i++)
    {
        cout << (*s[i].rbegin())[1] << " ";
    }


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