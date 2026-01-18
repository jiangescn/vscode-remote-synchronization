#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    map<int, int> s;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        s[a]++;
    }
    int ji = 0;
    int ou = 0;
    for (auto it: s)
    {
        if(it.first % 2)
        {
            ji += it.second;
        }
        else
        {
            ou += it.second;
        }
    }
    cout << min(ji, ou) << endl;

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