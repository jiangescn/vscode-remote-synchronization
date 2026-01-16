#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int data[5][5] = {0};
    map<int, pair<int, int>> s;
    for (int i = 1; i <= 9; i++)
    {
        for(int j = 1; j<= 9; j++)
        {
            int a;
            cin >> a;
            s[a] = {i, j};
        }
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